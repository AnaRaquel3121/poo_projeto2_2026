#include "Sensor.hpp"
#include <iostream>

Sensor::Sensor(int id, const std::string& divisao, TipoSensor tipo)
    : id(id), divisao(divisao), estado(false), tipo(tipo), comando(nullptr) {}

void Sensor::setComando(ComandoAlarme* comando) {
    this->comando = comando;
}

void Sensor::ativar() {
    estado = true;
    std::cout << "[SENSOR " << id << "] Ativado na divisao " << divisao << std::endl;
    if (comando != nullptr) {
        notificar();
    }
}

void Sensor::desativar() {
    estado = false;
    std::cout << "[SENSOR " << id << "] Desativado" << std::endl;
}

void Sensor::notificar() const {
    if (comando != nullptr) {
        comando->processarSensor(getTipoString(), divisao);
    }
}

void Sensor::fixaEstado(bool estado) {
    this->estado = estado;
    std::cout << "[SENSOR " << id << "] Estado fixado para " << (estado ? "ativo" : "inativo") << std::endl;
}

int Sensor::getId() const {
    return id;
}

std::string Sensor::getDivisao() const {
    return divisao;
}

bool Sensor::getEstado() const {
    return estado;
}

TipoSensor Sensor::getTipo() const {
    return tipo;
}

std::string Sensor::getTipoString() const {
    switch (tipo) {
        case TipoSensor::INTRUSAO: return "Intrusao";
        case TipoSensor::MOVIMENTO: return "Movimento";
        case TipoSensor::FOGO: return "Fogo";
        case TipoSensor::GAS: return "Gas";
        case TipoSensor::INUNDACAO: return "Inundacao";
        default: return "Desconhecido";
    }
}