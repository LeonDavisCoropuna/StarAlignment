#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include <vector>
#include "Sequence.h"
#include "FastaReader.h" // <- Aquí se espera que tengas una función o clase que lea archivos fasta

// Mock del contenido .fasta para el test
const std::string fastaContent =
    ">Raton gi|6679863|ref|NP_032070.1| frataxin [Mus musculus]\n"
    "MWAFGGRAAVGLLPRTASRASAWVGNPRWREPIVTCGRRGLHVTVNAGATRHAHLNLHYLQILNIKKQSV\n"
    "CVVHLRNLGTLDNPSSLDETAYERLAEETLDSLAEFFEDLADKPYTLEDYDVSFGDGVLTIKLGGDLGTY\n"
    "VINKQTPNKQIWLSSPSSGPKRYDWTGKNWVYSHDGVSLHELLARELTKALNTKLDLSSLAYSGKGT\n"
    "\n"
    ">Rata gi|109463707|ref|XP_001078791.1| PREDICTED: similar to Frataxin, mitochondrial precursor (Fxn) [Rattus norvegicus]\n"
    "MWTFGRRAAAGLLPRTASRASAWVRNPRGRERIGTCGRRGLHVTANADAIRHSHLNLHYLGQILNIKKQS\n"
    "VCVVHLRNSGTLGNPSSLDETAYERLAEETLDALAEFFEDLADKPYTLKDYDVSFGDGVLTIKLGGDLGT\n"
    "YVINKQTPNKQIWLSSPSSGPKRYDWTGKNWVYSHDGVSLHELLARELTEALNTKLDLSSLAYSGKGT\n";

TEST(FastaReaderTest, ReadMultipleSequences)
{
  // Crear archivo temporal de prueba
  const std::string filename = "temp_test.fasta";
  std::ofstream outFile(filename);
  outFile << fastaContent;
  outFile.close();

  // Leer las secuencias desde el archivo
  std::vector<Sequence> sequences = FastaReader::readFastaFile(filename);

  ASSERT_EQ(sequences.size(), 2);

  EXPECT_EQ(sequences[0].getId(), "Raton gi|6679863|ref|NP_032070.1| frataxin [Mus musculus]");
  EXPECT_EQ(sequences[0].getData().substr(0, 9), "MWAFGGRAA");

  EXPECT_EQ(sequences[1].getId(), "Rata gi|109463707|ref|XP_001078791.1| PREDICTED: similar to Frataxin, mitochondrial precursor (Fxn) [Rattus norvegicus]");
  EXPECT_EQ(sequences[1].getData().substr(0, 9), "MWTFGRRAA"); // Fragmento inicial

  // Eliminar archivo temporal
  std::remove(filename.c_str());
}

TEST(FastaReaderTest, ReadRealFastaFile)
{
  // Ruta relativa al archivo fasta real
  const std::string filename = "../data/frataxin_mamiferos.fasta";

  // Leer las secuencias desde el archivo
  std::vector<Sequence> sequences = FastaReader::readFastaFile(filename);

  // Validación básica (puedes ajustar según contenido real del archivo)
  ASSERT_GE(sequences.size(), 2); // Deben existir al menos 2 secuencias

  // Verifica contenido si sabes cómo empieza
  EXPECT_EQ(sequences[0].getId(), "Raton gi|6679863|ref|NP_032070.1| frataxin [Mus musculus]");
  EXPECT_EQ(sequences[0].getData().substr(0, 9), "MWAFGGRAA");

  EXPECT_EQ(sequences[1].getId(), "Rata gi|109463707|ref|XP_001078791.1| PREDICTED: similar to Frataxin, mitochondrial precursor (Fxn) [Rattus norvegicus]");
  EXPECT_EQ(sequences[1].getData().substr(0, 9), "MWTFGRRAA");
}