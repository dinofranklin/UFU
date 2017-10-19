package jogodedado;

import java.util.ArrayList;
import javax.swing.JOptionPane;

public class Teste {
    public static void main(String args[]){
        int maxNumber, nJogadores;
        maxNumber = Integer.parseInt(JOptionPane.showInputDialog("Entre com o numero maximo de pontos: "));
        nJogadores = Integer.parseInt(JOptionPane.showInputDialog("Entre com o numero de jogadores: "));
        
        JogoDeDado game = new JogoDeDado(nJogadores, maxNumber);
        while(!game.verificaVencedor()){
            game.rodada();
        }
        
        ArrayList <Jogador> vencedores = game.retornaVencedores();
        System.out.println("Vencedores: ");
        String nome;
        int pontuacao;
        for(Jogador j: vencedores){
            nome = j.retornaNome();
            pontuacao = j.retornaPontos();
            System.out.println(nome + " com " + pontuacao + " pontos");
        }
    }
}
