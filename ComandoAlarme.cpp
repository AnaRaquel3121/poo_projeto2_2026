#include "ComandoAlarme.hpp"
#include <iostream>

ComandoAlarme::ComandoAlarme()
    : estado(false), senha("0000"), mensagem("Sistema desarmado"), estadoCampainha(false),
      tentativas(0), MAX_TENTATIVAS(3) {}

ComandoAlarme::ComandoAlarme(const std::string& senhaInicial)
    : estado(false), senha(senhaInicial), mensagem("Sistema desarmado"), estadoCampainha(false),
      tentativas(0), MAX_TENTATIVAS(3) {}

void ComandoAlarme::armar(const std::string& senha) {
    if (senha == this->senha) {
        estado = true;
        mensagem = "Sistema armado com sucesso";
        resetTentativas();
        std::cout << "[ALARME] " << mensagem << std::endl;
    } else {
        mensagem = "Senha incorreta para armar";
        std::cout << "[ALARME] " << mensagem << std::endl;
    }
}

bool ComandoAlarme::desarmar(const std::string& senha) {
    if (senha == this->senha) {
        estado = false;
        estadoCampainha = false;
        mensagem = "Sistema desarmado";
        resetTentativas();
        std::cout << "[ALARME] " << mensagem << std::endl;
        return true;
    } else {
        tentativas++;
        if (tentativas >= MAX_TENTATIVAS) {
            ativarCampainha();
        }
        mensagem = "Senha incorreta. Tentativas: " + std::to_string(tentativas);
        std::cout << "[ALARME] " << mensagem << std::endl;
        return false;
    }
}

bool ComandoAlarme::mudarSenha(const std::string& senhaAntiga, const std::string& senhaNova) {
    if (senhaAntiga == senha) {
        if (senhaNova.length() == 4) {
            senha = senhaNova;
            mensagem = "Senha alterada com sucesso";
            std::cout << "[ALARME] " << mensagem << std::endl;
            return true;
        } else {
            mensagem = "Nova senha deve ter 4 digitos";
            std::cout << "[ALARME] " << mensagem << std::endl;
            return false;
        }
    } else {
        mensagem = "Senha atual incorreta";
        std::cout << "[ALARME] " << mensagem << std::endl;
        return false;
    }
}

void ComandoAlarme::processarSensor(const std::string& tipo, const std::string& divisao) {
    if (estado) {
        mensagem = "ALERTA: Sensor de " + tipo + " ativado na divisao " + divisao;
        std::cout << "[ALARME] " << mensagem << std::endl;
        std::cout << "[ALARME] Introduza a senha para desarmar (" << MAX_TENTATIVAS << " tentativas):" << std::endl;
    }
}

void ComandoAlarme::ativarCampainha() {
    estadoCampainha = true;
    mensagem = "CAMPANHA ATIVADA - ALARME SONORO";
    std::cout << "[ALARME] " << mensagem << std::endl;
}

void ComandoAlarme::desativarCampainha() {
    estadoCampainha = false;
    std::cout << "[ALARME] Campainha desativada" << std::endl;
}

void ComandoAlarme::resetTentativas() {
    tentativas = 0;
}

void ComandoAlarme::liga(const std::string& senha) {
    armar(senha);
}

void ComandoAlarme::desliga(const std::string& senha) {
    desarmar(senha);
}

bool ComandoAlarme::getEstado() const {
    return estado;
}

bool ComandoAlarme::getEstadoCampainha() const {
    return estadoCampainha;
}

std::string ComandoAlarme::getSenha() const {
    return senha;
}

std::string ComandoAlarme::getMensagem() const {
    return mensagem;
}

int ComandoAlarme::getTentativas() const {
    return tentativas;
}

int ComandoAlarme::getMaxTentativas() const {
    return MAX_TENTATIVAS;
}