/**
 * @file ComandoAlarme.hpp
 * @brief Declaração da classe ComandoAlarme que representa o sistema de alarme doméstico
 * @author Ana Raquel
 * @date 2026
 *
 * Este ficheiro contém a declaração da classe ComandoAlarme que gere
 * o estado do sistema de alarme, autenticação por senha e controle
 * da campainha.
 */

#ifndef COMANDOALARME_HPP
#define COMANDOALARME_HPP

#include <string>

/**
 * @class ComandoAlarme
 * @brief Classe que representa o sistema de alarme doméstico
 *
 * A classe ComandoAlarme é responsável por:
 * - Gerir o estado do sistema (armado/desarmado)
 * - Validar senhas de 4 dígitos
 * - Controlar a campainha de alarme
 * - Processar eventos de sensores
 *
 * @note A senha por omissão é "0000"
 */
class ComandoAlarme
{
private:
    bool estado;          /**< Estado do sistema: true=armado, false=desarmado */
    std::string senha;    /**< Senha de 4 dígitos do sistema */
    std::string mensagem; /**< Mensagem descritiva do último evento */
    bool estadoCampainha; /**< Estado da campainha: true=ativa, false=desativada */
    int tentativas;       /**< Número de tentativas de senha falhadas */

public:
    const int MAX_TENTATIVAS; /**< Máximo de tentativas permitidas (3) */
    /**
     * @brief Construtor por omissão
     * Inicializa o sistema com senha "0000" e estado desarmado
     */
    ComandoAlarme();

    /**
     * @brief Construtor com senha inicial
     * @param senhaInicial Senha de 4 dígitos para inicializar o sistema
     */
    ComandoAlarme(const std::string &senhaInicial);

    /**
     * @brief Arma o sistema de alarme
     * @param senha Senha para armar o sistema
     * @note Apenas arma se a senha for correta
     */
    void armar(const std::string &senha);

    /**
     * @brief Desarma o sistema de alarme
     * @param senha Senha para desarmar o sistema
     * @return true se desarmou com sucesso, false caso contrário
     * @note Se a senha estiver errada 3 vezes, ativa a campainha
     */
    bool desarmar(const std::string &senha);

    /**
     * @brief Altera a senha do sistema
     * @param senhaAntiga Senha atual do sistema
     * @param senhaNova Nova senha de 4 dígitos
     * @return true se alterou com sucesso, false caso contrário
     * @note A nova senha deve ter exatamente 4 dígitos
     */
    bool mudarSenha(const std::string &senhaAntiga, const std::string &senhaNova);

    /**
     * @brief Processa a ativação de um sensor
     * @param tipo Tipo do sensor ativado
     * @param divisao Divisão onde o sensor foi ativado
     * @note Exibe mensagem de alerta e informa sobre tentativas
     */
    void processarSensor(const std::string &tipo, const std::string &divisao);

    /**
     * @brief Ativa a campainha de alarme
     * @note Usada quando se excede o número máximo de tentativas
     */
    void ativarCampainha();

    /**
     * @brief Desativa a campainha de alarme
     */
    void desativarCampainha();

    /**
     * @brief Reinicia o contador de tentativas
     */
    void resetTentativas();

    /**
     * @brief Pede a senha ao utilizador para desarmar o sistema
     * Lê a senha do stdin, verifica se correta e processa o resultado
     * @return true se desarmou com sucesso, false caso contrário
     * @note Se 3 tentativas erradas, ativa a campainha
     */
    bool pedirSenhaParaDesarmar();

    /**
     * @brief Liga o sistema (alias para armar)
     * @param senha Senha para ligar o sistema
     */
    void liga(const std::string &senha);

    /**
     * @brief Desliga o sistema (alias para desarmar)
     * @param senha Senha para desligar o sistema
     */
    void desliga(const std::string &senha);

    // ==================== Getters ====================

    /**
     * @brief Obtém o estado do sistema
     * @return true se armado, false se desarmado
     */
    bool getEstado() const;

    /**
     * @brief Obtém o estado da campainha
     * @return true se ativa, false se desativada
     */
    bool getEstadoCampainha() const;

    /**
     * @brief Obtém a senha atual do sistema
     * @return String com a senha
     */
    std::string getSenha() const;

    /**
     * @brief Obtém a última mensagem do sistema
     * @return String com a mensagem
     */
    std::string getMensagem() const;

    /**
     * @brief Obtém o número de tentativas atuais
     * @return Número de tentativas falhadas
     */
    int getTentativas() const;

    /**
     * @brief Obtém o número máximo de tentativas permitidas
     * @return Valor de MAX_TENTATIVAS
     */
    int getMaxTentativas() const;
};

#endif