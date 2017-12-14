package view;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import javax.swing.ImageIcon;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class MesaView {
    JPanel painel, mesa, historico, centro, cartas;
    JFrame janela;
    JLabel placar;
    
    public MesaView() {
        
        //CRIANDO PAINEIS E JANELA.
        janela = new JFrame("Jogo de Truco");
        painel = new JPanel(new BorderLayout());
        mesa = new JPanel(new GridLayout(3,3));
        historico = new JPanel();
        centro = new JPanel(new BorderLayout());
        cartas = new JPanel(new GridLayout(1,4));
        placar = new JLabel();
        
        //ADICIONANDO OS PAINEIS NO PRINCIPAL.
        centro.add(cartas, BorderLayout.CENTER);
        centro.add(placar, BorderLayout.NORTH);
        
        painel.add(mesa, BorderLayout.CENTER);
        painel.add(historico, BorderLayout.SOUTH);
        
        janela.add(painel);
        janela.setSize(1600,1000);
        janela.setVisible(true);
        janela.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        System.out.println("CRIEI TUDO");
    }
    
    
    public void atualizarPlacar(int d1, int d2, int ptd1, int ptd2, int apostados){
        String s = "Dupla " + d1 + " " + ptd1 + " vs " + ptd2 + " Dupla " + d2 + " Pontos apostados: " + apostados;
        centro.remove(placar);
        placar = new JLabel(s);
        centro.add(placar, BorderLayout.NORTH);
        centro.revalidate();
        centro.repaint();
    }
    
    public void limparCartas(){
        centro.remove(cartas);
        cartas = new JPanel();
        centro.add(cartas, BorderLayout.CENTER);
        centro.revalidate();
        centro.repaint();
    }
    
    public void fazerMesa(JogadorView j1, JogadorView j2, JogadorView j3, JogadorView j4){
        
        mesa.add(new JPanel());
        mesa.add(j1.getPrincipal());
        mesa.add(new JPanel());
        
        mesa.add(j3.getPrincipal());
        mesa.add(centro);
        mesa.add(j4.getPrincipal());
        
        mesa.add(new JPanel());
        mesa.add(j2.getPrincipal());
        mesa.add(new JPanel());
        
        mesa.revalidate();
        mesa.repaint();
        painel.revalidate();
        painel.revalidate();
        janela.revalidate();
        janela.repaint();
        
        System.out.println("ADICIONEI JOGADORES");
    }
    
    public void atualizaCentro(CartaView c){
        
        ImageIcon card = new ImageIcon(getClass().getResource(c.getEndereco()));
        
        JPanel novaCarta = new JPanel();
        novaCarta.add(new JLabel(card));
        
        cartas.add(novaCarta);
        cartas.revalidate();
        cartas.repaint();
    }

    public JFrame getJanela() {
        return janela;
    }
    
}
