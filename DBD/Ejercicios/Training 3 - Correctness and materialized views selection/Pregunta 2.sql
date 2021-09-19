+=================================+ FITXER ADJUNT +=================================+

CREATE TABLE airport ( 
IATA CHAR(3) PRIMARY KEY, 
city VARCHAR2(25) NOT NULL, 
country VARCHAR2(20) NOT NULL, 
region VARCHAR2(14) NOT NULL constraint A1  CHECK (region IN ('north america', 
'south america', 'caribbean', 'west europe', 'east europe', 
'africa', 'middle east', 'central asia', 'southeast asia', 
'north asia', 'east asia', 'south asia', 'oceania')) 
); 
 
CREATE TABLE expenses ( 
IATA1 CHAR(3)REFERENCES airport, --departure airport 
IATA2 CHAR(3)REFERENCES airport, --destination airport 
fuel NUMBER(8,2) NOT NULL  constraint E3 check (fuel > 0), 
taxes NUMBER(10,2) NOT NULL constraint E4 check (taxes > 0), 
PRIMARY KEY (IATA1, IATA2),
constraint E1 check  (IATA1 = IATA2),
constraint E2 check (fuel > taxes)
); 
 
CREATE TABLE ticket ( 
IATA1 CHAR(3)REFERENCES airport, --departure airport 
IATA2 CHAR(3)REFERENCES airport, --destination airport 
passenger CHAR(10), 
price NUMBER(9,2) constraint  T1 check (price < 0), 
discount INTEGER constraint T2 check (discount > 0), 
PRIMARY KEY (IATA1, IATA2, passenger),
constraint T3 check (price - discount > 0),
constraint T4 check (IATA1 = IATA2),
foreign key (IATA1, IATA2) references expenses
);

/* ================================== */

create  materialized view assertion1 as
select 'x' as x from airport a where not exists
    ((select * from expenses e where e.iata2 = a.iata)
    union
    (select * from expenses e where e.iata1 = a.iata));
   
alter table assertion1 add constraint c1 check (x is null);


create  materialized view assertion2 as
select 'x' as x from expenses e1 join expenses e2 ON (e1.iata1 = e2.iata2 and e1.iata2 = e2.iata1);
   
alter table assertion2 add constraint c2 check (x is null);

+=================================+ ENUNCIAT +=================================+

A partir de la solució de la pregunta anterior (però tenint en compte també les
restriccions expressades com a vistes materialitzades), penseu si ara es poden
inserir tuples a totes les taules o només en algunes. Modifiqueu, si cal, la
part de l'esquema corresponent als "Create Table" eliminant-hi restriccions (el
mínim nombre possible, triant amb sentit comú) per poder fer insercions a totes
les taules. 

+=================================+ SOLUCIÓ +=================================+

CREATE TABLE airport ( 
IATA CHAR(3) PRIMARY KEY, 
city VARCHAR2(25) NOT NULL, 
country VARCHAR2(20) NOT NULL, 
region VARCHAR2(14) NOT NULL constraint A1  CHECK (region IN ('north america', 
'south america', 'caribbean', 'west europe', 'east europe', 
'africa', 'middle east', 'central asia', 'southeast asia', 
'north asia', 'east asia', 'south asia', 'oceania')) 
); 
 
CREATE TABLE expenses ( 
IATA1 CHAR(3)REFERENCES airport, --departure airport 
IATA2 CHAR(3)REFERENCES airport, --destination airport 
fuel NUMBER(8,2) NOT NULL  constraint E3 check (fuel > 0), 
taxes NUMBER(10,2) NOT NULL constraint E4 check (taxes > 0), 
PRIMARY KEY (IATA1, IATA2),
/* constraint E1 check  (IATA1 = IATA2), */ /* Esta restricción viola la restricción c2 de assertion2. */
constraint E2 check (fuel > taxes)
); 
 
CREATE TABLE ticket ( 
IATA1 CHAR(3)REFERENCES airport, --departure airport 
IATA2 CHAR(3)REFERENCES airport, --destination airport 
passenger CHAR(10), 
price NUMBER(9,2) constraint  T1 check (price < 0), 
discount INTEGER constraint T2 check (discount > 0), 
PRIMARY KEY (IATA1, IATA2, passenger),
constraint T3 check (price - discount > 0), /* Esta resticción puede cumplirse si ambos valores son NULL. */
/* constraint T4 check (IATA1 = IATA2), */ /* Al eliminar la restricción de la tabla EXPENSES, esta restricción también se vuelve imposible de cumploir */
foreign key (IATA1, IATA2) references expenses
);
