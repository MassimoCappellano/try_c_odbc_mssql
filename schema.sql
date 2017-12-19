-- EXAMPLE
CREATE TABLE CUSTOMERS 
(
    CustomerID  nvarchar(64) NOT NULL,
    ContactName nvarchar(64) NOT NULL, 
    Phone nvarchar(64) NOT NULL
)

INSERT INTO CUSTOMERS (CustomerID, ContactName, Phone) VALUES ('AAA', 'PIPPO', '123456');
INSERT INTO CUSTOMERS (CustomerID, ContactName, Phone) VALUES ('BBB', 'PLUTO', '323456');
INSERT INTO CUSTOMERS (CustomerID, ContactName, Phone) VALUES ('CCC', 'PAPERINO', '723456');