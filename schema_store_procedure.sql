CREATE SEQUENCE LIGHTS_DATA_ID_ST
    START WITH 1
    INCREMENT BY 1
    NO CACHE
    ;
GO

CREATE TABLE LIGHTS_DATA_ST
(
    ID bigint PRIMARY KEY NOT NULL DEFAULT (NEXT VALUE FOR dbo.LIGHTS_DATA_ID_ST),
    MAC_ADDRESS VARCHAR(20) NOT NULL,
    tensione NUMERIC(19, 4) NOT NULL,
    dataRilevazione DATETIME NOT NULL,
    tipoMisura INT NOT NULL,
    serviceName NVARCHAR(50)
);
GO

CREATE PROCEDURE [dbo].[AxCreateLightMeasure]
	@macAddress VARCHAR(20), 
	@tensione NUMERIC(19, 4), 
	@dataRilevazione DATETIME,
	@tipoMisura INT, 
	@serviceName NVARCHAR(50)
AS
BEGIN

    INSERT INTO LIGHTS_DATA_ST 
        (mac_Address, tensione, dataRilevazione, tipoMisura, serviceName)
    VALUES
        (@macAddress, @tensione, @dataRilevazione, @tipoMisura, @serviceName)

    RETURN 1

END
GO

use GATEWAY_DATA  
IF EXISTS (SELECT name FROM sysobjects WHERE name = 'TestParm')  
   DROP PROCEDURE TestParm  
GO  

CREATE PROCEDURE TestParm   
@OutParm int OUTPUT   
AS  
SELECT @OutParm = 88  
RETURN 99  
go  

	