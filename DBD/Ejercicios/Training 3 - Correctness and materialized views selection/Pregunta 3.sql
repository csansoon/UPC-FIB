+=================================+ FITXER ADJUNT +=================================+

create view TE as select t.iata1, t.iata2 from ticket t where 50 * t.discount >
    (select e.fuel + e.taxes from expenses e where e.iata1 = t.iata1 and e.iata2 = t.iata2)

+=================================+ ENUNCIAT +=================================+

A partir de la solució de la pregunta anterior (però tenint en compte també les
restriccions expressades com a vistes materialitzades), pensa si la vista adjunta
té la propietat de liveliness. En cas afirmatiu, proposa uns INSERT (el mínim
nombre possible) d'exemple. En cas negatiu, no responguis a través del corrector;
justifica la resposta en paper.

+=================================+ SOLUCIÓ +=================================+

INSERT INTO airport VALUES ('BCN', 'Barcelona', 'Spain', 'west europe');
INSERT INTO airport VALUES ('MDR', 'Madrid', 'Spain', 'west europe');
INSERT INTO EXPENSES VALUES ('BCN', 'MDR', 10, 5);
INSERT INTO ticket VALUES('BCN', 'MDR', 'passenger2', null, 5);
