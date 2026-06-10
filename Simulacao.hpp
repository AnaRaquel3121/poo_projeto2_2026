/**
 * @file Simulacao.hpp
 * @brief Declaração da classe Simulacao para gestão de eventos
 * @author Ana Raquel
 * @date 2026
 *
 * Este ficheiro contém a declaração da classe Simulacao que é
 * responsável por gerir a fila de eventos e executar a simulação
 * do sistema de alarme.
 */

#ifndef SIMULACAO_HPP
#define SIMULACAO_HPP

#include <string>
#include <queue>
#include <vector>
#include "ComandoAlarme.hpp"
#include "Sensor.hpp"

/**
 * @struct Evento
 * @brief Estrutura que representa um evento na fila
 *
 * Um evento é composto por um tipo e até dois parâmetros
 * que detalham a ação a ser executada.
 */
struct Evento {
    std::string tipo;   /**< Tipo do evento (ARMAR, DESARMAR, ATIVAR, etc.) */
    std::string param1; /**< Primeiro parâmetro do evento */
    std::string param2; /**< Segundo parâmetro do evento (opcional) */
};

/**
 * @class Simulacao
 * @brief Classe que gere a simulação do sistema de alarme
 *
 * A classe Simulacao é responsável por:
 * - Carregar eventos de um ficheiro de texto
 * - Processar eventos sequencialmente (FIFO)
 * - Gerir a coleção de sensores
 * - Coordenar a comunicação entre sensores e ComandoAlarme
 *
 * @note Os eventos são processados por ordem de chegada (FIFO)
 */
class Simulacao {
private:
    std::queue<Evento> eventos;         /**< Fila de eventos a processar */
    std::vector<Sensor*> sensores;       /**< Vetor de ponteiros para sensores */
    ComandoAlarme* comandoAlarme;        /**< Ponteiro para o ComandoAlarme */

    /**
     * @brief Carrega eventos de um ficheiro de texto
     * @param ficheiro Nome do ficheiro contendo os eventos
     * @return true se carregou com sucesso, false caso contrário
     * @note Cada linha do ficheiro deve conter um evento no formato:
     *       TIPO [param1] [param2]
     */
    bool carregarEventos(const std::string& ficheiro);

    /**
     * @brief Analisa uma linha do ficheiro e cria um Evento
     * @param linha Linha a analisar
     * @param evento Evento a preencher com os dados
     * @return true se a linha foi processada com sucesso
     *
     * Tipos de eventos suportados:
     * - ARMAR <senha>
     * - DESARMAR <senha>
     * - MUDARSENHA <senha_antiga> <senha_nova>
     * - ATIVAR <id_sensor>
     */
    bool parseEvento(const std::string& linha, Evento& evento);

    /**
     * @brief Processa um evento individual
     * @param evento Evento a processar
     * @note Executa a ação correspondente ao tipo de evento
     */
    void processarEvento(const Evento& evento);

public:
    /**
     * @brief Construtor da classe Simulacao
     */
    Simulacao();

    /**
     * @brief Destrutor da classe Simulacao
     */
    ~Simulacao();

    /**
     * @brief Adiciona um sensor à simulação
     * @param sensor Ponteiro para o sensor a adicionar
     */
    void adicionarSensor(Sensor* sensor);

    /**
     * @brief Associa um ComandoAlarme à simulação
     * @param comando Ponteiro para o ComandoAlarme
     * @note Também associa o comando a todos os sensores já adicionados
     */
    void setComandoAlarme(ComandoAlarme* comando);

    /**
     * @brief Inicia a simulação carregando eventos do ficheiro
     * @param ficheiroEventos Nome do ficheiro de eventos
     * @return true se iniciou com sucesso, false caso contrário
     */
    bool iniciar(const std::string& ficheiroEventos);

    /**
     * @brief Executa a simulação processando todos os eventos
     * @note Processa eventos em ordem FIFO até a fila ficar vazia
     */
    void executar();

    /**
     * @brief Obtém um sensor pelo seu ID
     * @param id ID do sensor a procurar
     * @return Ponteiro para o sensor ou nullptr se não encontrado
     */
    Sensor* obtemSensor(int id) const;
};

#endif