#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <string>
#include "ComandoAlarme.hpp"

enum class TipoSensor {
    INTRUSAO,
    MOVIMENTO,
    FOGO,
    GAS,
    INUNDACAO
};

class Sensor {
private:
    int id;
    std::string divisao;
    bool estado;
    TipoSensor tipo;
    ComandoAlarme* comando;

public:
    Sensor(int id, const std::string& divisao, TipoSensor tipo);
    void setComando(ComandoAlarme* comando);

    void ativar();
    void desativar();
    void notificar() const;
    void fixaEstado(bool estado);

    int getId() const;
    std::string getDivisao() const;
    bool getEstado() const;
    TipoSensor getTipo() const;
    std::string getTipoString() const;
};

#endif