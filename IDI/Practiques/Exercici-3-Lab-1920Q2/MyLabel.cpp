#include "MyLabel.h"

// Constructor:
MyLabel::MyLabel(QWidget *parent): QLabel(parent) {
    ences = false;
    
    moviments = 0;
    max_moviments = 15;
    
    verd = "border: 2px solid #00890f; background-color: #00ff1c";
    groc = "border: 2px solid #898300; background-color: #fff300";
    vermell = "border: 2px solid #890000; background-color: #ff0000";
    
    estat_endevant  = "Endevant";
    estat_enrera    = "Enrera";
    estat_esquerra  = "Esquerra";
    estat_dreta     = "Dreta";
    estat_gir       = "Gir";
    estat_on        = "Funcionant...";
    estat_off       = "Apagat";
}

// Implementació slots:
void MyLabel::mostra(QString &text) {
    
    emit actualitza_text(text);
}

void MyLabel::encen_o_apaga() {
    
    ences = !ences;
    emit habilita_o_deshabilita(ences);
    
    if (ences) {
        emit actualitza_color(verd);
        emit actualitza_text(estat_on);
    }
    else {
        emit actualitza_color(vermell);
        emit actualitza_text(estat_off);
        moviments = 0;
        emit mostra_moviments(moviments);
    }
    
}

void MyLabel::incrementa_moviments() {
    ++moviments;
    emit mostra_moviments(moviments);
    
    if (moviments >= max_moviments) {
        emit clica_boto();
    }
    else if (moviments >= 10) {
        emit actualitza_color(groc);
    }
    
}


void MyLabel::control_endevant() {
    emit mostra(estat_endevant);
    emit incrementa_moviments();
}
void MyLabel::control_enrera() {
    emit mostra(estat_enrera);
    emit incrementa_moviments();
}
void MyLabel::control_esquerra() {
    emit mostra(estat_esquerra);
    emit incrementa_moviments();
}
void MyLabel::control_dreta() {
    emit mostra(estat_dreta);
    emit incrementa_moviments();
}
void MyLabel::control_gir(const int &) {
    emit mostra(estat_gir);
}

