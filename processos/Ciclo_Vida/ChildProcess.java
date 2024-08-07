public class ChildProcess {

    public static void main(String[] args) {
        // Imprime o ID do processo filho
        long childPid = ProcessHandle.current().pid();
        System.out.println("Este é o processo filho, com o id " + childPid);
    }
}
