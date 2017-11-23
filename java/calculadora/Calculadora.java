package calculadora;

import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class Calculadora {
    
    public void janela(){
        
        JFrame principal = new JFrame("Calculadora");
        principal.setSize(200,300);
        Container conte = principal.getContentPane();
        conte.setLayout(new BorderLayout());
        JTextField texto = new JTextField(20);
        JPanel botoes = new JPanel(new GridLayout(4,3));
        JPanel control = new JPanel();
        JPanel operacao = new JPanel(new GridLayout(5,1));
        conte.add(texto, BorderLayout.NORTH);
        conte.add(botoes, BorderLayout.CENTER);
        conte.add(operacao, BorderLayout.EAST);
        conte.add(control, BorderLayout.SOUTH);
        JButton sair = new JButton("sair");
        JButton limpar = new JButton("limpar");
        control.add(limpar);
        control.add(sair);
        
        sair.addActionListener((ActionEvent e) -> {
            System.exit(0);
        });
        
        limpar.addActionListener((ActionEvent e) -> {
            texto.setText("");
        });
        
        String[] ops = {"+","-","*","/","="};
        String[] num = {"1","2","3","4","5","6","7","8","9","","0",""};
        
        ActionListener tratanum = new ActionListener(){
            public void actionPerformed(ActionEvent e){
                JButton bt = (JButton) e.getSource();
                texto.setText(texto.getText() + bt.getText());
            }
        };
                
        ActionListener trataop = new ActionListener(){
            public void actionPerformed(ActionEvent e){
                JButton bt = (JButton) e.getSource();
                String t = texto.getText();
                System.out.println("Chegou com = " + t);
                if(bt.getText().equals("=")){
                    Eval conta = new Eval(t);
                    if(conta.evaluate() == false) texto.setText("EXPRESSAO INVALIDA");
                    else texto.setText("" + conta.getAns());
                }
                else{
                    texto.setText(texto.getText() + bt.getText());
                }
            }
        };
        
        
        for(int i=0; i<ops.length; ++i){
            ((JButton)operacao.add(new JButton(ops[i]))).addActionListener(trataop);
        }
        
        for(int i=0; i<num.length; ++i){
            ((JButton)botoes.add(new JButton(num[i]))).addActionListener(tratanum);
        }
        
        principal.setVisible(true);
    }
    
    public static void main(String[] args) {
        Calculadora calc = new Calculadora();
        calc.janela();
    }
    
}
