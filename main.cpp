/**
 * @file main.cpp
 * @brief Programa principal com menu interativo
 * @author Ana Raquel
 * @date 2026
 *
 * Este ficheiro contem o programa principal que oferece uma interface
 * de menu interativo para controlar o sistema de alarme domestico.
 */

#include <iostream>
#include <string>
#include <limits>
#include "ComandoAlarme.hpp"
#include "Sensor.hpp"
#include "Simulacao.hpp"

/**
 * @brief Mostra o menu principal do sistema
 */
void mostrarMenu()
{
    std::cout << "\n========================================" << std::endl;
    std::cout << "        MENU SISTEMA DE ALARME" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << " 1. Armar sistema" << std::endl;
    std::cout << " 2. Desarmar sistema" << std::endl;
    std::cout << " 3. Ativar sensor" << std::endl;
    std::cout << " 4. Ver estado do sistema" << std::endl;
    std::cout << " 5. Listar sensores" << std::endl;
    std::cout << " 6. Mudar senha" << std::endl;
    std::cout << " 7. Carregar eventos de ficheiro" << std::endl;
    std::cout << " 0. Sair" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << " Escolha uma opcao: ";
}

/**
 * @brief Mostra o estado atual do sistema
 * @param comando Ponteiro para o ComandoAlarme
 */
void mostrarEstado(ComandoAlarme *comando)
{
    std::cout << "\n--- ESTADO DO SISTEMA ---" << std::endl;
    std::cout << "Sistema: " << (comando->getEstado() ? "ARMADO" : "DESARMADO") << std::endl;
    std::cout << "Campainha: " << (comando->getEstadoCampainha() ? "ATIVA" : "DESATIVA") << std::endl;
    std::cout << "Tentativas: " << comando->getTentativas() << "/" << comando->getMaxTentativas() << std::endl;
    std::cout << "Mensagem: " << comando->getMensagem() << std::endl;
}

/**
 * @brief Lista todos os sensores cadastrados
 * @param simulacao Ponteiro para a Simulacao
 */
void listarSensores(Simulacao *simulacao)
{
    std::cout << "\n--- SENSORES ---" << std::endl;
    for (int i = 1; i <= 5; i++)
    {
        Sensor *s = simulacao->obtemSensor(i);
        if (s != nullptr)
        {
            std::cout << "Sensor " << s->getId() << ": "
                      << s->getDivisao() << " | "
                      << s->getTipoString() << " | "
                      << (s->getEstado() ? "ATIVO" : "INATIVO")
                      << std::endl;
        }
    }
}

/**
 * @brief Desativa todos os sensores
 * @param simulacao Ponteiro para a Simulacao
 */
void desativarTodosSensores(Simulacao *simulacao)
{
    for (int i = 1; i <= 5; i++)
    {
        Sensor *s = simulacao->obtemSensor(i);
        if (s != nullptr && s->getEstado())
        {
            s->desativar();
        }
    }
}

/**
 * @brief Programa principal com menu interativo
 * @return 0 se execucao bem sucedida
 */
int main()
{
    std::cout << "========================================" << std::endl;
    std::cout << "   SISTEMA DE ALARME DOMESTICO" << std::endl;
    std::cout << "========================================" << std::endl;

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

    std::cout << "[MAIN] Sistema iniciado" << std::endl;
    std::cout << "[MAIN] 5 sensores criados" << std::endl;
    std::cout << "[MAIN] Senha por omissao: 0000" << std::endl;

    int opcao;
    bool sair = false;

    while (!sair)
    {
        mostrarMenu();
        std::cin >> opcao;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "[ERRO] Opcao invalida. Introduza um numero." << std::endl;
            continue;
        }

        switch (opcao)
        {
        case 1:
        {
            std::string senha;
            std::cout << "Introduza a senha: ";
            std::cin >> senha;
            comando.armar(senha);
            break;
        }
        case 2:
        {
            std::string senha;
            std::cout << "Introduza a senha: ";
            std::cin >> senha;
            if (comando.desarmar(senha))
            {
                desativarTodosSensores(&simulacao);
            }
            break;
        }
        case 3:
        {
            listarSensores(&simulacao);
            int id;
            std::cout << "ID do sensor a ativar: ";
            std::cin >> id;
            Sensor *s = simulacao.obtemSensor(id);
            if (s != nullptr)
            {
                s->ativar();
                if (comando.getEstado() && !comando.getEstadoCampainha())
                {
                    for (int i = 0; i < comando.getMaxTentativas(); i++)
                    {
                        if (comando.pedirSenhaParaDesarmar())
                        {
                            desativarTodosSensores(&simulacao);
                            break;
                        }
                    }
                }
            }
            else
            {
                std::cout << "[ERRO] Sensor nao existe." << std::endl;
            }
            break;
        }
        case 4:
        {
            mostrarEstado(&comando);
            break;
        }
        case 5:
        {
            listarSensores(&simulacao);
            break;
        }
        case 6:
        {
            std::string senhaAntiga, senhaNova;
            std::cout << "Senha atual: ";
            std::cin >> senhaAntiga;
            std::cout << "Nova senha (4 digitos): ";
            std::cin >> senhaNova;
            comando.mudarSenha(senhaAntiga, senhaNova);
            break;
        }
        case 7:
        {
            std::string ficheiro;
            std::cout << "Nome do ficheiro de eventos: ";
            std::cin >> ficheiro;
            if (simulacao.iniciar(ficheiro))
            {
                simulacao.executar();
            }
            break;
        }
        case 0:
        {
            std::cout << "A sair do sistema..." << std::endl;
            sair = true;
            break;
        }
        default:
        {
            std::cout << "[ERRO] Opcao invalida." << std::endl;
            break;
        }
        }
    }

    std::cout << "Sistema terminado." << std::endl;
    return 0;
}