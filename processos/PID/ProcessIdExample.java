import java.io.BufferedReader;
import java.io.InputStreamReader;

public class ProcessIdExample {
    public static void main(String[] args) {
        try {
            // Obtém o PID do processo atual
            String pid = getProcessId();
            // Obtém o PID do pai do processo
            String ppid = getParentProcessId();

            System.out.println("O id do processo é " + pid);
            System.out.println("O id do pai do processo é " + ppid);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // Método para obter o PID do processo atual
    private static String getProcessId() throws Exception {
        String pid = null;
        // O comando 'ps -o pid=' retorna o PID do processo atual
        Process process = Runtime.getRuntime().exec("ps -o pid=");
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        pid = reader.readLine().trim();
        reader.close();
        return pid;
    }

    // Método para obter o PID do pai do processo
    private static String getParentProcessId() throws Exception {
        String ppid = null;
        // O comando 'ps -o ppid= -p <PID>' retorna o PID do pai do processo
        String pid = getProcessId(); // Obtém o PID do processo atual
        Process process = Runtime.getRuntime().exec("ps -o ppid= -p " + pid);
        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
        ppid = reader.readLine().trim();
        reader.close();
        return ppid;
    }
}
