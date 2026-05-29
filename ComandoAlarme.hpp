#ifndef COMANDOALARME_HPP
#define COMANDOALARME_HPP

#include <string>

class ComandoAlarme {
private:
    bool estado;
    std::string senha;
    std::string mensagem;
    bool estadoCampainha;
    int tentativas;
    const int MAX_TENTATIVAS;

public:
    ComandoAlarme();
    ComandoAlarme(const std::string& senhaInicial);

    void armar(const std::string& senha);
    bool desarmar(const std::string& senha);
    bool mudarSenha(const std::string& senhaAntiga, const std::string& senhaNova);

    void processarSensor(const std::string& tipo, const std::string& divisao);
    void ativarCampainha();
    void desativarCampainha();
    void resetTentativas();

    void liga(const std::string& senha);
    void desliga(const std::string& senha);

    bool getEstado() const;
    bool getEstadoCampainha() const;
    std::string getSenha() const;
    std::string getMensagem() const;
    int getTentativas() const;
    int getMaxTentativas() const;
};

#endif