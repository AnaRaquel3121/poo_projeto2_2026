#ifndef SIMULACAO_HPP
#define SIMULACAO_HPP

#include <string>
#include <queue>
#include <vector>
#include "ComandoAlarme.hpp"
#include "Sensor.hpp"

struct Evento {
    std::string tipo;
    std::string param1;
    std::string param2;
};

class Simulacao {
private:
    std::queue<Evento> eventos;
    std::vector<Sensor*> sensores;
    ComandoAlarme* comandoAlarme;

    bool carregarEventos(const std::string& ficheiro);
    bool parseEvento(const std::string& linha, Evento& evento);
    void processarEvento(const Evento& evento);

public:
    Simulacao();
    ~Simulacao();

    void adicionarSensor(Sensor* sensor);
    void setComandoAlarme(ComandoAlarme* comando);
    bool iniciar(const std::string& ficheiroEventos);
    void executar();
    Sensor* obtemSensor(int id) const;
};

#endif