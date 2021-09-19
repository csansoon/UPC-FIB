/* +=================================+ FITXER ADJUNT +=================================+ */

CREATE TABLE CentMilResp(
  ref INTEGER PRIMARY KEY,
  pobl INTEGER NOT NULL,
  edat INTEGER NOT NULL,
  cand INTEGER NOT NULL,
  val INTEGER NOT NULL,
  UNIQUE (pobl, edat, cand)
);

/* +=================================+ ENUNCIAT +=================================+ */
/*
Suposa que tenim una taula CentMilResp(ref, pobl, edat, cand, val) (pots trobarla sentencia de creació al fitxer adjunt).
  - D=1seg; C=0; BT=10000; |T| = 100000; Ndist(pobl)= 200; Ndist(edat)=100; Ndist(cand)=10
  - La mitjana d'informació de control per tupla ocupa el mateix que un atribut
  - Tots els atributs ocupen el mateix i la freqüència de les consultes és:
    1. 35%: SELECT cand, MAX(val) FROM CentMilResp GROUP BY cand;
    2. 20%: SELECT cand, edat, AVG(val), MAX(val), MIN(val) FROM CentMilResp GROUP BY cand, edat;
    3. 20%: SELECT pobl, MAX(val) FROM CentMilResp GROUP BY cand, pobl;
    4. 25%: SELECT pobl, MAX(val) FROM CentMilResp GROUP BY pobl; 

Considera les dades donades i fes servir l'algorisme greedy per a decidir quines vistes materialitzar (suposant que el
temps de la update window és il·limitat, que tenim 10140 blocs de disc i donant preferència a vistes que coincideixen
amb alguna consulta en cas d'empat). Suposa també que el mecanisme de rescriptura és prou bo com per utilitzar una vista
materialitzada encara que no coincideixi exactament amb la consulta si amb la informació de la vista es pot calcular el
que especifica la consulta.

Manté sempre els noms dels atributs de la taula original (es a dir, no utilitzis cap alias a la definició de la vista).
Totes les vistes han de tenir la reescriptura activada, construir-se de forma inmediata y refrescar-se de forma completa
sota demanda.
*/
/* +=================================+ SOLUCIÓ +=================================+ */

??????????????????????????????????????
