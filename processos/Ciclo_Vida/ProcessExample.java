public class ProcessExample {

    public static void main(String[] args) {
        // Imprime o ID do processo principal
        long parentPid = ProcessHandle.current().pid();
        System.out.println("O id do processo do programa principal é " + parentPid);

        // Cria um novo processo
        ProcessBuilder processBuilder = new ProcessBuilder("java", "-cp", ".", "ChildProcess");
        try {
            Process process = processBuilder.start();

            // Espera o processo filho terminar
            process.waitFor();

            // Imprime informações sobre o processo pai
            System.out.println("Este é o processo pai, com o id " + parentPid);
            System.out.println("O id do processo filho não é diretamente acessível em Java.");
            
        } catch (IOException | InterruptedException e) {
            System.err.println("Erro ao criar ou esperar o processo: " + e.getMessage());
        }
    }
}
