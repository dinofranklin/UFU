package view;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class JogadorView {
    private JPanel principal, botoes, cartas;
    private final JButton trucar, correr, aumentar, aceitar;
    
    public JogadorView(String nome){
        
        //DECLARAÇÃO DOS PAINEIS.
        this.principal = new JPanel(new BorderLayout());
        this.botoes = new JPanel(new GridLayout(4,1));
        this.cartas = new JPanel(new GridLayout(1,3));
        
        //DECLARAÇÃO DOS BOTOES.
        this.trucar = new JButton("Trucar");
        this.correr = new JButton("Correr");
        this.aumentar = new JButton("Aumentar");
        this.aceitar = new JButton("Aceitar");
        
        //ADICIONANDO PAINEIS NO PRINCIPAL.
        this.principal.add(new JLabel("Jogador: " + nome), BorderLayout.NORTH);
        this.principal.add(botoes, BorderLayout.EAST);
        this.principal.add(cartas, BorderLayout.CENTER);
        
        //ADICIONANDO BOTOES.
        this.botoes.add(this.trucar);
        this.botoes.add(this.correr);
        this.botoes.add(this.aumentar);
        this.botoes.add(this.aceitar);
        
        System.out.println("FIZ O JOGADOR!");
    }
    
    //ADICIONAR/REMOVER CARTAS.
    
    public void limparCartas(){
        cartas.removeAll();
        cartas.revalidate();
        cartas.repaint();
        principal.revalidate();
        principal.repaint();
    }
    
    
    public void removerCarta(CartaView c){
        cartas.remove(c.getBotao());
        cartas.add(new CartaView("carta", "virada").getBotao());
        
        cartas.revalidate();
        cartas.repaint();
        principal.revalidate();
        principal.repaint();
    }
    
    
    public void setCarta(CartaView c){
        cartas.add(c.getBotao());
        cartas.revalidate();
        cartas.repaint();
        principal.revalidate();
        principal.repaint();
    }
    
    
    //GETTERS.

    public JButton getAceitar() {
        return aceitar;
    }

    public JButton getAumentar() {
        return aumentar;
    }

    public JButton getCorrer() {
        return correr;
    }

    public JButton getTrucar() {
        return trucar;
    }

    public JPanel getPrincipal() {
        return principal;
    }
    
    
    //HABILITAR/DESABILITAR BOTOES.
    
    public void habilitarTruco(){
        trucar.setEnabled(true);
    }
    
    public void habilitarCorrer(){
        correr.setEnabled(true);
    }
    
    public void habilitarAumentar(){
        aumentar.setEnabled(true);
    }
    
    public void habilitarAceitar(){
        aceitar.setEnabled(true);
    }
    
    public void desabilitarTruco(){
        trucar.setEnabled(false);
    }
    
    public void desabilitarCorrer(){
        correr.setEnabled(false);
    }
    
    public void desabilitarAumentar(){
        aumentar.setEnabled(false);
    }
    
    public void desabilitarAceitar(){
        aceitar.setEnabled(false);
    }
}
