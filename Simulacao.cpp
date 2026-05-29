#include "Simulacao.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

Simulacao::Simulacao() : comandoAlarme(nullptr) {}

Simulacao::~Simulacao() {}

void Simulacao::adicionarSensor(Sensor* sensor) {
    sensores.push_back(sensor);
}

void Simulacao::setComandoAlarme(ComandoAlarme* comando) {
    comandoAlarme = comando;
    for (Sensor* sensor : sensores) {
        sensor->setComando(comando);
    }
}

bool Simulacao::carregarEventos(const std::string& ficheiro) {
    std::ifstream ficheiroEventos(ficheiro);
    if (!ficheiroEventos.is_open()) {
        std::cout << "[ERRO] Nao foi possivel abrir o ficheiro: " << ficheiro << std::endl;
        return false;
    }

    std::string linha;
    while (std::getline(ficheiroEventos, linha)) {
        if (linha.empty()) continue;

        Evento evento;
        if (parseEvento(linha, evento)) {
            eventos.push(evento);
        }
    }

    ficheiroEventos.close();
    std::cout << "[SIMULACAO] Carregados " << eventos.size() << " eventos" << std::endl;
    return true;
}

bool Simulacao::parseEvento(const std::string& linha, Evento& evento) {
    std::istringstream iss(linha);
    std::string tipo;
    iss >> tipo;

    if (tipo == "ARMAR") {
        iss >> evento.param1;
        evento.tipo = "ARMAR";
        evento.param2 = "";
        return true;
    } else if (tipo == "DESARMAR") {
        iss >> evento.param1;
        evento.tipo = "DESARMAR";
        evento.param2 = "";
        return true;
    } else if (tipo == "MUDARSENHA") {
        iss >> evento.param1 >> evento.param2;
        evento.tipo = "MUDARSENHA";
        return true;
    } else if (tipo == "ATIVAR") {
        iss >> evento.param1;
        evento.tipo = "ATIVAR";
        evento.param2 = "";
        return true;
    } else if (tipo == "DESATIVAR") {
        iss >> evento.param1;
        evento.tipo = "DESATIVAR";
        evento.param2 = "";
        return true;
    }

    return false;
}

void Simulacao::processarEvento(const Evento& evento) {
    std::cout << "\n--- Processando evento: " << evento.tipo;
    if (!evento.param1.empty()) std::cout << " " << evento.param1;
    if (!evento.param2.empty()) std::cout << " " << evento.param2;
    std::cout << " ---" << std::endl;

    if (evento.tipo == "ARMAR") {
        comandoAlarme->armar(evento.param1);
    }
    else if (evento.tipo == "DESARMAR") {
        comandoAlarme->desarmar(evento.param1);
    }
    else if (evento.tipo == "MUDARSENHA") {
        comandoAlarme->mudarSenha(evento.param1, evento.param2);
    }
    else if (evento.tipo == "ATIVAR") {
        int idSensor = std::stoi(evento.param1);
        for (Sensor* sensor : sensores) {
            if (sensor->getId() == idSensor) {
                sensor->ativar();
                break;
            }
        }
    }
    else if (evento.tipo == "DESATIVAR") {
        int idSensor = std::stoi(evento.param1);
        for (Sensor* sensor : sensores) {
            if (sensor->getId() == idSensor) {
                sensor->desativar();
                break;
            }
        }
    }
}

bool Simulacao::iniciar(const std::string& ficheiroEventos) {
    std::cout << "[SIMULACAO] A iniciar simulacao..." << std::endl;
    if (!carregarEventos(ficheiroEventos)) {
        return false;
    }
    std::cout << "[SIMULACAO] Eventos carregados com sucesso" << std::endl;
    return true;
}

void Simulacao::executar() {
    std::cout << "\n========================================" << std::endl;
    std::cout << "       INICIO DA SIMULACAO" << std::endl;
    std::cout << "========================================" << std::endl;

    while (!eventos.empty()) {
        Evento evento = eventos.front();
        eventos.pop();
        processarEvento(evento);
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "       FIM DA SIMULACAO" << std::endl;
    std::cout << "========================================" << std::endl;
}

Sensor* Simulacao::obtemSensor(int id) const {
    for (Sensor* sensor : sensores) {
        if (sensor->getId() == id) {
            return sensor;
        }
    }
    return nullptr;
}