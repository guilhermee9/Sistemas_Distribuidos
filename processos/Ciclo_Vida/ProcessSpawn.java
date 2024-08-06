import java.io.IOException;

public class ProcessSpawn {

    // Método para criar e executar um processo filho
    private static Process spawn(String program, String[] argList) throws IOException {
        ProcessBuilder processBuilder = new ProcessBuilder(argList);
        // Define o programa a ser executado
        processBuilder.command(program);
        return processBuilder.start();
    }

    public static void main(String[] args) {
        // Lista de argumentos para o comando "ls"
        String[] argList = {
            "ls",   // argv[0], o nome do programa
            "-l",
            "/"    // Diretório para listar
        };

        try {
            // Gera um processo filho executando o comando "ls"
            Process process = spawn("ls", argList);

            // Espera até que o processo filho termine
            process.waitFor();
            System.out.println("O programa principal terminou");
        } catch (IOException e) {
            System.err.println("Ocorreu um erro ao executar o processo");
            e.printStackTrace();
        } catch (InterruptedException e) {
            System.err.println("O processo foi interrompido");
            e.printStackTrace();
        }
    }
}
