// Copyright 2021 University of Washington Applied Physics Laboratory
//

#include <utility>
#include <algorithm>

#include "sonar_image_proc/AbstractSonarInterface.h"

namespace sonar_image_proc {

const Bounds_t UnsetBounds = Bounds_t(-1, -1);

Bounds_t AbstractSonarInterface::azimuthBounds() const {
    if (_azimuthBounds == UnsetBounds) {
         auto results = std::minmax_element(azimuths().begin(), azimuths().end());
        _azimuthBounds = std::make_pair(*(results.first), *(results.second));
    }

    return _azimuthBounds;
}

Bounds_t AbstractSonarInterface::rangeBounds() const {
    if (_rangeBounds == UnsetBounds) {
        auto results = std::minmax_element(ranges().begin(), ranges().end());
        _rangeBounds = std::make_pair(*(results.first), *(results.second));
    }

    return _rangeBounds;
}


}