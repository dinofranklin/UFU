package jogodedado;

import java.util.ArrayList;
import javax.swing.JOptionPane;

public class JogoDeDado {
    int nroRodadas, maxNumber;
    ArrayList<Jogador> jogadores;
    
    public JogoDeDado(int n, int m){
        this.jogadores = new ArrayList<Jogador>();
        this.nroRodadas = 1;
        this.maxNumber = m;
        String nome;
        for(int i=1; i<=n; ++i){
            nome = JOptionPane.showInputDialog("Entre com o nome do jogador " + i + ":");
            Jogador j = new Jogador(nome);
            jogadores.add(j);
        }
    }
    
    public void rodada(){
        System.out.println("Rodada " + nroRodadas + ":");
        this.nroRodadas++;
        String nome;
        int valorJogado, valorTotal;
        for(Jogador j: jogadores){
            valorJogado = j.rolarDado();
            valorTotal = j.retornaPontos();
            nome = j.retornaNome();
            System.out.println("Jogador " + nome + " jogou " + valorJogado + " e com total de " + valorTotal);
        }
    }
    
    public boolean verificaVencedor(){
        for(Jogador j: jogadores){
            if(j.retornaPontos() >= this.maxNumber){
                return true;
            }
        }
        return false;
    }
    
    public ArrayList<Jogador> retornaVencedores(){
        ArrayList<Jogador> vencedores = new ArrayList<Jogador>();
        for(Jogador j: jogadores){
            if(j.retornaPontos() >= this.maxNumber){
                vencedores.add(j);
            }
        }
        return vencedores;
    }
}
