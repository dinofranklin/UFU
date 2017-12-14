package controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.util.ArrayList;
import javax.swing.JOptionPane;
import model.Dupla;
import model.JogadorModel;
import view.MenuView;

public class MenuController {
    MenuView view;
    ArrayList<JogadorModel> jogadores = new ArrayList<>();
    ArrayList<Dupla> duplas = new ArrayList<>();
    
    public MenuController(){
        view = new MenuView();
        
        view.getBotaoJogador().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                view.desabilitarPrincipal();
                view.habilitarCampoJogador();
            }
        });
        
        view.getBotaoDuplas().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                view.desabilitarPrincipal();
                view.habilitarCampoDuplas();
            }
        });
        
        
        view.getBotaoJogPronto().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                String nome = view.getNome1();
                jogadores.add(new JogadorModel(nome));
                view.habilitarPrincipal();
                view.limparCampo();
            }
        });
        
        view.getBotaoDupPronto().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                String nome1 = view.getNome1();
                String nome2 = view.getNome2();
                
                JogadorModel j1 = encontraJogador(nome1);
                JogadorModel j2 = encontraJogador(nome2);
                
                
                if(j1 != null && j2 != null && j1 != j2){
                    duplas.add(new Dupla(j1, j2, duplas.size()));
                }
                else JOptionPane.showMessageDialog(null, "Nao ha nenhum jogador com esse nome!\n");
                
                view.habilitarPrincipal();
                view.limparCampo();
            }
        });
        
        
        view.getBotaoJogar().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                jogar();
            }
        });
        
        view.getBotaoSair().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                System.exit(0);
            }
        });
        
        view.getBotaoListar().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                listarJogadores();
                listarDuplas();
            }
        });
    }
    
    public void listarJogadores(){
        String imprime = "Jogadores cadastrados:\n";
        for(JogadorModel j: jogadores){
            imprime += j.getNome() + "\n";
        }
        JOptionPane.showMessageDialog(null, imprime);
    }
    
    public void listarDuplas(){
        String imprime = "Duplas cadastradas:\n";
        for(int i=0; i<duplas.size(); ++i){
            imprime += duplas.get(i).imprime();
        }
        JOptionPane.showMessageDialog(null, imprime);
    }
    
    
    public Dupla encontraDupla(){
        String imprime = "Duplas cadastradas:\n";
        for(int i=0; i<duplas.size(); ++i){
            imprime += duplas.get(i).imprime();
        }
        int p = Integer.parseInt(JOptionPane.showInputDialog(imprime+"\nEscolha um numero"));
        if(p < 1 || p > duplas.size()){
            JOptionPane.showMessageDialog(null, "Dupla nao valida!\n");
        }
        
        return duplas.get(p-1);
    }
    
    
    public void jogar(){
        if(duplas.size() < 2){
            JOptionPane.showMessageDialog(null, "Voce precisa cadastrar pelo menos duas duplas");
            return;
        }
        if(duplas.size() > 2){
            Dupla d1, d2;
            
            d1 = encontraDupla();
            if(d1 == null) return;
            d2 = encontraDupla();
            if(d2 == null) return;
            
            if(d1.getJ1()==d2.getJ1() || d1.getJ1()==d2.getJ2() || d1.getJ2()==d2.getJ2() || d1.getJ2() == d2.getJ1()){
                JOptionPane.showMessageDialog(null, "Um ou mais jogadores pertencem a duplas diferentes!");
            }
            
            else chama_controller(d1, d2);
        }
        else{
            chama_controller(duplas.get(0), duplas.get(1));
        }
    }
    
    
    public void chama_controller(Dupla d1, Dupla d2){
        ControllerJogo jogo = new ControllerJogo(d1, d2);
        
        view.getMenu().setEnabled(false);
        
        //DESABILITA JANELA DE MENU- SO VOLTA QUANDO O JOGO FECHAR.
        
        jogo.getJogo().getMesa().getJanela().addWindowListener(new WindowAdapter(){
            public void windowClosing(WindowEvent e){
                d1.fimDeJogo();
                d2.fimDeJogo();
                view.getMenu().setEnabled(true);
                e.getWindow().dispose();
            }
            
            public void windowClosed(WindowEvent e){
                d1.fimDeJogo();
                d2.fimDeJogo();
                view.getMenu().setEnabled(true);
                e.getWindow().dispose();
            }
        });
        
    }
    
    
    public JogadorModel encontraJogador(String nome){
        for(JogadorModel j: jogadores){
            if(nome.equals(j.getNome())) return j;
        }
        return null;
    }
    
    
    public static void main(String[] args){
        ArrayList<JogadorModel> jogadores = new ArrayList<>();
        
        MenuController m = new MenuController();
        JogadorModel j1, j2, j3, j4;
        j1 = new JogadorModel("ariosvaldo");
        j2 = new JogadorModel("glenio");
        j3 = new JogadorModel("jeremias");
        j4 = new JogadorModel("cleiton");
        m.jogadores.add(j1);
        m.jogadores.add(j2);
        m.jogadores.add(j3);
        m.jogadores.add(j4);
        
        m.duplas.add(new Dupla(j1, j2, 1));
        m.duplas.add(new Dupla(j3, j4, 2));
                
    }
}
