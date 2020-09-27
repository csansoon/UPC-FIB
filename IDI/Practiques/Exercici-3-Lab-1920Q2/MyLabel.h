#include <QLabel>

class MyLabel: public QLabel
{
    
    Q_OBJECT
    
public:
    
    MyLabel (QWidget *parent);
    
    
public slots:
    
    void mostra(QString &);

    void encen_o_apaga();
    
    void incrementa_moviments();
    
    void control_endevant();
    void control_enrera();
    void control_esquerra();
    void control_dreta();
    void control_gir(const int &);
    
signals: //No s'han d'implementar
    
    void habilita_o_deshabilita(const bool &);
    void actualitza_text(const QString &);
    void actualitza_color(const QString &);
    void clica_boto();
    void mostra_moviments(const int &);
    

private:
    bool ences;
    int moviments, max_moviments;
    QString verd, groc, vermell;
    QString estat_endevant, estat_enrera, estat_esquerra, estat_dreta, estat_gir, estat_on, estat_off;
};
