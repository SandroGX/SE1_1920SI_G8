/* Faz a iniciação do controlador e configura os respetivos pinos. */
void SPI_Init(void);

//min 390625 Hz max 100M Hz
/* Configura o ritmo de envio/receção, o numero de bits de dados e o modo (CPOL, CPHA). */
void SPI_ConfigTransfer(int frequency, int bitData, int mode);

/* Realiza uma transferência. Retorna sucesso ou erro na transferência. */
int SPI_Transfer(unsigned short *txBuffer, unsigned short *rxBuffer, int length);

/* Realiza uma transferência. Retorna sucesso ou erro na transferência. buffer com unidade de um byte*/
int SPI_Transfer8(unsigned char *txBuffer, unsigned char *rxBuffer, int length);
