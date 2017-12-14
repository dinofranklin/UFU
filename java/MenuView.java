package view;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class MenuView {
    JFrame menu;
    JPanel botoes, princ, text;
    JButton duplas, jogador, jogpronto, duppronto, sair, jogar, listar;
    JTextField nome1, nome2;
    
    public MenuView(){
        menu = new JFrame("Menu - Jogo de Truco");
        
        //CRIANDO BOTOES
        duplas = new JButton("Cadastrar dupla");
        jogador = new JButton("Cadastrar jogador");
        jogpronto = new JButton("Pronto!");
        duppronto = new JButton("Pronto!");
        jogar = new JButton("Jogar!");
        listar = new JButton("Listar");
        sair = new JButton("Sair!");
        
        //CRIANDO PAINEIS
        botoes = new JPanel();
        princ = new JPanel();
        text = new JPanel();
        
        //ADICIONANDO BOTOES NO PAINEL
        botoes.add(duplas);
        botoes.add(jogador);
        botoes.add(jogar);
        botoes.add(listar);
        botoes.add(sair);
        
        //CRIANDO TEXT FIELDS
        nome1 = new JTextField(25);
        nome2 = new JTextField(25);
      
        //ADICIONANDO PAINEIS NO FRAME.
        princ.add(botoes);
        princ.add(text);
        menu.add(princ);
        menu.setSize(700,200);
        menu.setVisible(true);
        menu.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    
    //RETORNA OS BOTOES PARA O CONTROLLER.

    public JButton getBotaoDuplas() {
        return duplas;
    }

    public JButton getBotaoJogador() {
        return jogador;
    }

    public JButton getBotaoJogPronto() {
        return jogpronto;
    }
    
    public JButton getBotaoDupPronto() {
        return duppronto;
    }

    public JButton getBotaoJogar() {
        return jogar;
    }

    public JButton getBotaoSair() {
        return sair;
    }
    
    public JButton getBotaoListar(){
        return listar;
    }
    
    //DESABILITA O CAMPO PRINCIPAL.

    public void desabilitarPrincipal() {
        duplas.setEnabled(false);
        jogador.setEnabled(false);
    }
    
    //HABILITA O CAMPO PRINCIPAL.
    
    public void habilitarPrincipal() {
        duplas.setEnabled(true);
        jogador.setEnabled(true);
    }
    
    //HABILITA O CAMPO JOGADOR PARA O USUARIO.
    
    public void habilitarCampoJogador(){
        JPanel campos = new JPanel(new GridLayout(5,1));
        campos.add(new JLabel("Nome do Jogador: "));
        campos.add(nome1); nome1.setText("");
        campos.add(jogpronto);
        text.add(campos);
        text.revalidate();
    }
    
    //HABILITA O CAMPO DUPLAS PARA O USUARIO.
    
    public void habilitarCampoDuplas(){
        JPanel campos = new JPanel(new GridLayout(5,1));
        campos.add(new JLabel("Nome do Jogador 1: "));
        campos.add(nome1); nome1.setText("");
        campos.add(new JLabel("Nome do Jogador 2: "));
        campos.add(nome2); nome2.setText("");
        campos.add(duppronto);
        text.add(campos);
        text.revalidate();
    }
    
    //LIMPA O CAMPO TEXTO.
    
    public void limparCampo(){
        text.removeAll();
        text.revalidate();
    }
    
    //RETORNA O NOME DOS JOGADORES.
    
    public String getNome1(){
        return nome1.getText();
    }
    
    public String getNome2(){
        return nome2.getText();
    }

    public JFrame getMenu() {
        return menu;
    }
    
}
