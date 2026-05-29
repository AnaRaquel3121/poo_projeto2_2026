#include <iostream>
#include <string>
#include "ComandoAlarme.hpp"
#include "Sensor.hpp"
#include "Simulacao.hpp"

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "   SISTEMA DE ALARME DOMESTICO" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << std::endl;

    ComandoAlarme comando("0000");

    Simulacao simulacao;
    simulacao.setComandoAlarme(&comando);

    Sensor sensor1(1, "Sala", TipoSensor::MOVIMENTO);
    Sensor sensor2(2, "Cozinha", TipoSensor::GAS);
    Sensor sensor3(3, "Quarto", TipoSensor::INTRUSAO);
    Sensor sensor4(4, "Casa de Banho", TipoSensor::INUNDACAO);
    Sensor sensor5(5, "Entrada", TipoSensor::INTRUSAO);

    simulacao.adicionarSensor(&sensor1);
    simulacao.adicionarSensor(&sensor2);
    simulacao.adicionarSensor(&sensor3);
    simulacao.adicionarSensor(&sensor4);
    simulacao.adicionarSensor(&sensor5);

    std::cout << "[MAIN] Sensores criados: " << 5 << std::endl;
    std::cout << "[MAIN] Divisoes: Sala, Cozinha, Quarto, Casa de Banho, Entrada" << std::endl;
    std::cout << "[MAIN] Senha por omissao: 0000" << std::endl;
    std::cout << std::endl;

    if (!simulacao.iniciar("eventos.dados")) {
        std::cout << "[ERRO] Falha ao iniciar simulacao" << std::endl;
        return 1;
    }

    simulacao.executar();

    return 0;
}