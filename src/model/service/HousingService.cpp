#include "model/service/HousingService.h"
#include "model/entity/IHasDiscount.h"
#include <thread>
#include <vector>
#include <numeric>
#include <algorithm>
#include <stdexcept>

void HousingService::settleApartment(
    House& house,
    int number,
    const std::vector<std::shared_ptr<ITenant>>& tenants
) {
    Apartment& apt = house.findApartment(number);
    apt.setTenants(tenants);
}

void HousingService::correctApartmentData(
    House& house,
    int number,
    const Apartment& updated
) {
    Apartment& apt = house.findApartment(number);
    apt = updated;
}

void HousingService::vacateApartment(
    House& house,
    int number
) {
    Apartment& apt = house.findApartment(number);
    apt.setTenants({});
}

double HousingService::calculatePaymentForApartment(
    const House& house,
    int number
) const {
    const Apartment& apt = house.findApartment(number);

    double basePayment = apt.getArea() * house.getPaymentPerSqMeter();
    double tenantPayment = apt.getTenantCount() * house.getPaymentPerTenant();
    double total = basePayment + tenantPayment;

    double maxDiscount = 0.0;
    for (const auto& tenant : apt.getTenants()) {
        if (auto* d = dynamic_cast<const IHasDiscount*>(tenant.get())) {
            if (d->getDiscount() > maxDiscount) {
                maxDiscount = d->getDiscount();
            }
        }
    }

    return total * (1.0 - maxDiscount);
}

double HousingService::calculateApartmentDiscount(const Apartment& apt) const {
    double total = 0.0;
    for (const auto& tenant : apt.getTenants()) {
        if (auto* d = dynamic_cast<const IHasDiscount*>(tenant.get())) {
            total += d->getDiscount();
        }
    }
    return total;
}

double HousingService::calculateTotalDiscountsSingleThread(
    const House& house
) const {
    double total = 0.0;
    for (auto it = house.begin(); it != house.end(); ++it) {
        total += calculateApartmentDiscount(it->value);
    }
    return total;
}

double HousingService::calculateTotalDiscountsMultiThread(
    const House& house
) const {
    auto begin = house.begin();
    auto end = house.end();

    if (begin == end) {
        return 0.0;
    }

    size_t total_size = std::distance(begin, end);

    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 1;
    }
    if (num_threads > total_size) {
        num_threads = static_cast<unsigned int>(total_size);
    }

    size_t chunk_size = (total_size + num_threads - 1) / num_threads;

    std::vector<std::thread> threads;
    std::atomic<double> total{0.0};

    for (unsigned int i = 0; i < num_threads; ++i) {
        auto chunk_begin = begin + i * chunk_size;
        if (chunk_begin >= end) {
            break;
        }
        auto chunk_end = std::min(chunk_begin + chunk_size, end);

        threads.emplace_back([this, chunk_begin, chunk_end, &total]() {
            double local_sum = 0.0;
            for (auto it = chunk_begin; it != chunk_end; ++it) {
                local_sum += calculateApartmentDiscount(it->value);
            }
            total += local_sum;
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    return total.load();
}
