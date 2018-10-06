#pragma once

#include "point.hpp"
#include <vector>
#include <initializer_list>
#include <memory>

class StoppingCriterion {
public:
    virtual bool stop(const Point&, double, size_t,
                      const std::vector<Point, double>&) {
        assert(false);
        return true;
    } 
};

class StoppingCriteria {
    std::vector<std::unique_ptr<StoppingCriterion>> criteria_;

public:
    StoppingCriteria() {};

    template <typename T, typename... Args>
    void add(Args&&... args) {
        criteria_.emplace_back(new T(std::forward<Args>(args)...));
    }

    bool stop(const Point& x, double val, size_t iter,
              const std::vector<Point, double>& path) {
        for (auto& criterion : criteria_) {
            if (criterion->stop(x, val, iter, path)) {
                return true;
            }
        }
        return false;
    }
};