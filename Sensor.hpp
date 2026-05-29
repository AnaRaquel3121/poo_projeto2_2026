/**
 * @file Sensor.hpp
 * @brief Declaração da classe Sensor e do enum TipoSensor
 * @author Ana Raquel
 * @date 2026
 *
 * Este ficheiro contém a declaração da classe Sensor que representa
 * os sensores do sistema de alarme doméstico, bem como a enumeração
 * TipoSensor para categorizar os diferentes tipos de sensores.
 */

#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <string>
#include "ComandoAlarme.hpp"

/**
 * @enum TipoSensor
 * @brief Tipos de sensores disponíveis no sistema
 *
 * O sistema suporta 5 tipos de sensores:
 * - INTRUSAO: Sensores de abertura de portas/janelas
 * - MOVIMENTO: Sensores de movimento interior
 * - FOGO: Sensores de deteção de incêndio
 * - GAS: Sensores de fuga de gás
 * - INUNDACAO: Sensores de inundação
 */
enum class TipoSensor {
    INTRUSAO,   /**< Sensor de intrusão (portas/janelas) */
    MOVIMENTO,  /**< Sensor de movimento interior */
    FOGO,       /**< Sensor de fogo */
    GAS,        /**< Sensor de fuga de gás */
    INUNDACAO   /**< Sensor de inundação */
};

/**
 * @class Sensor
 * @brief Classe que representa um sensor do sistema de alarme
 *
 * Cada sensor está associado a uma divisão específica e pode ser
 * de um dos 5 tipos definidos. Quando ativado, notifica o
 * ComandoAlarme ao qual está associado.
 *
 * @note Um sensor pode estar ativo (detectou algo) ou inativo
 */
class Sensor {
private:
    int id;                              /**< Identificador único do sensor */
    std::string divisao;                 /**< Nome da divisão onde o sensor está localizado */
    bool estado;                          /**< Estado do sensor: true=ativo, false=inativo */
    TipoSensor tipo;                      /**< Tipo do sensor (ver TipoSensor) */
    ComandoAlarme* comando;               /**< Ponteiro para o ComandoAlarme associado */

public:
    /**
     * @brief Construtor da classe Sensor
     * @param id Identificador único do sensor
     * @param divisao Nome da divisão onde o sensor está
     * @param tipo Tipo de sensor (ver TipoSensor)
     */
    Sensor(int id, const std::string& divisao, TipoSensor tipo);

    /**
     * @brief Associa o sensor a um ComandoAlarme
     * @param comando Ponteiro para o ComandoAlarme
     * @note Esta associação permite ao sensor notificar o alarme quando ativado
     */
    void setComando(ComandoAlarme* comando);

    /**
     * @brief Ativa o sensor
     * Quando ativado, o sensor notifica automaticamente o ComandoAlarme
     * @see notificar()
     */
    void ativar();

    /**
     * @brief Desativa o sensor
     * Coloca o sensor no estado inativo
     */
    void desativar();

    /**
     * @brief Notifica o ComandoAlarme sobre a ativação
     * @note Método interno chamado automaticamente por ativar()
     */
    void notificar() const;

    /**
     * @brief Define o estado do sensor
     * @param estado true para ativar, false para desativar
     */
    void fixaEstado(bool estado);

    // ==================== Getters ====================

    /**
     * @brief Obtém o ID do sensor
     * @return ID do sensor
     */
    int getId() const;

    /**
     * @brief Obtém o nome da divisão
     * @return String com o nome da divisão
     */
    std::string getDivisao() const;

    /**
     * @brief Obtém o estado do sensor
     * @return true se ativo, false se inativo
     */
    bool getEstado() const;

    /**
     * @brief Obtém o tipo do sensor
     * @return Valor do enum TipoSensor
     */
    TipoSensor getTipo() const;

    /**
     * @brief Obtém o tipo do sensor em formato string
     * @return String com o nome do tipo
     */
    std::string getTipoString() const;
};

#endif