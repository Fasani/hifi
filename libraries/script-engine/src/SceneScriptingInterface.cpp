//
//  SceneScriptingInterface.cpp
//  interface/src/scripting
//
//  Created by Sam Gateau on 2/24/15.
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#include <AddressManager.h>

#include "SceneScriptingInterface.h"

void SceneScriptingInterface::setStageOrientation(const glm::quat& orientation) {
    _skyStage->setOriginOrientation(orientation);
}
void SceneScriptingInterface::setStageLocation(float longitude, float latitude, float altitude) {
    _skyStage->setOriginLocation(longitude, latitude, altitude);
}

float SceneScriptingInterface::getStageLocationLongitude() const {
    return _skyStage->getOriginLongitude();
}
float SceneScriptingInterface::getStageLocationLatitude() const {
    return _skyStage->getOriginLatitude();
}
float SceneScriptingInterface::getStageLocationAltitude() const {
    return _skyStage->getOriginSurfaceAltitude();
}

void SceneScriptingInterface::setStageDayTime(float hour) {
    _skyStage->setDayTime(hour);
}

float SceneScriptingInterface::getStageDayTime() const {
    return _skyStage->getDayTime();
}

void SceneScriptingInterface::setStageYearTime(int day) {
    _skyStage->setYearTime(day);
}

int SceneScriptingInterface::getStageYearTime() const {
    return _skyStage->getYearTime();
}

void SceneScriptingInterface::setSunColor(const glm::vec3& color) {
    _skyStage->setSunColor(color);
}

const glm::vec3& SceneScriptingInterface::getSunColor() const {
    return _skyStage->getSunColor();
}

void SceneScriptingInterface::setSunIntensity(float intensity) {
    _skyStage->setSunIntensity(intensity);
}

float SceneScriptingInterface::getSunIntensity() const {
    return _skyStage->getSunIntensity();
}

void SceneScriptingInterface::setSunAmbientIntensity(float intensity) {
    _skyStage->setSunAmbientIntensity(intensity);
}

float SceneScriptingInterface::getSunAmbientIntensity() const {
    return _skyStage->getSunAmbientIntensity();
}

void SceneScriptingInterface::setSunDirection(const glm::vec3& direction) {
    _skyStage->setSunDirection(direction);
}

const glm::vec3& SceneScriptingInterface::getSunDirection() const {
    return _skyStage->getSunDirection();
}

void SceneScriptingInterface::setStageEarthSunModelEnable(bool isEnabled) {
    _skyStage->setEarthSunModelEnable(isEnabled);
}

bool SceneScriptingInterface::isStageEarthSunModelEnabled() const {
    return _skyStage->isEarthSunModelEnabled();
}

model::SunSkyStagePointer SceneScriptingInterface::getSkyStage() const {
    return _skyStage;
}

void SceneScriptingInterface::setShouldRenderAvatars(bool shouldRenderAvatars) {
    if (shouldRenderAvatars != _shouldRenderAvatars) {
        _shouldRenderAvatars = shouldRenderAvatars;
        emit shouldRenderAvatarsChanged(_shouldRenderAvatars);
    }
}

void SceneScriptingInterface::setShouldRenderEntities(bool shouldRenderEntities) {
    if (shouldRenderEntities != _shouldRenderEntities) {
        _shouldRenderEntities = shouldRenderEntities;
        emit shouldRenderEntitiesChanged(_shouldRenderEntities);
    }
}