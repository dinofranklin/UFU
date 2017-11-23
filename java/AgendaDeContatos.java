package agendadecontatos;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import javax.swing.*;

public class AgendaDeContatos {

    public static void main(String[] args) {
        
        JButton procurar = new JButton("Procurar");
        JButton cadastrar = new JButton("Cadastrar");
        JButton apagar = new JButton("Apagar");
        JButton sair = new JButton("Sair");
        JButton listar = new JButton("Listar");
        
        JFrame janela = new JFrame("Agenda de Contatos");
        janela.setSize(400,200);
        JPanel painel = new JPanel();
        
        JLabel nome = new JLabel("Nome: ");
        JLabel endereco = new JLabel("Endereco: ");
        JLabel telefone = new JLabel("Telefone: ");
        JLabel titulo = new JLabel("Entre com os dados\n");
        
        JTextField campoNome = new JTextField(25);
        JTextField campoEndereco = new JTextField(25);
        JTextField campoTelefone = new JTextField(25);
        
        painel.add(nome);
        painel.add(campoNome);
        painel.add(telefone);
        painel.add(campoTelefone);
        painel.add(endereco);
        painel.add(campoEndereco);
        painel.add(procurar);
        painel.add(cadastrar);
        painel.add(apagar);
        painel.add(sair);
        painel.add(listar);
        
        janela.getContentPane().add(painel);
        janela.setVisible(true);
        
        ArrayList<Contato> contatos = new ArrayList<>();
        
        cadastrar.addActionListener(new ActionListener(){
            public void actionPerformed (ActionEvent e){
                String nomePessoa = campoNome.getText();
                String telPessoa = campoTelefone.getText();
                String endPessoa = campoEndereco.getText();
                contatos.add(new Contato(nomePessoa, telPessoa, endPessoa));
                campoNome.setText("");
                campoTelefone.setText("");
                campoEndereco.setText("");
                JOptionPane.showMessageDialog(null, "Contato adicionado");
            }
        });
        
        apagar.addActionListener(new ActionListener(){
            public void actionPerformed (ActionEvent e){
                String nomePessoa = campoNome.getText();
                for(Contato c: contatos){
                    if(nomePessoa.equals(c.getName())){
                        contatos.remove(c);
                    }
                }
                campoNome.setText("");
                campoTelefone.setText("");
                campoEndereco.setText("");
                JOptionPane.showMessageDialog(null, "Contato apagado");
            }
        });
        
        procurar.addActionListener(new ActionListener(){
            public void actionPerformed (ActionEvent e){
                String nomePessoa = campoNome.getText();
                for(Contato c: contatos){
                    if(nomePessoa.equals(c.getName())){
                        String imprime = "Nome: " + c.getName() + "\n";
                        imprime += "Endereco: " + c.getEndereco() + "\n";
                        imprime += "Telefone: " + c.getTelefone() + "\n";
                        JOptionPane.showMessageDialog(null, imprime);
                    }
                }
                campoNome.setText("");
                campoTelefone.setText("");
                campoEndereco.setText("");
            }
        });
        
        sair.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                System.exit(0);
            }
        });
            
        listar.addActionListener(new ActionListener(){
            public void actionPerformed (ActionEvent e){
                String imprime = "";
                for(Contato c: contatos){
                    imprime += "Nome: " + c.getName() + "\n";   
                    imprime += "Endereco: " + c.getEndereco() + "\n";
                    imprime += "Telefone: " + c.getTelefone() + "\n";
                    imprime += "-----------------------------------------\n";
                }
                JOptionPane.showMessageDialog(null, imprime);
            }
        });
    }
}
    