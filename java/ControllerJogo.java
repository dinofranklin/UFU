package controller;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import model.CartaModel;
import model.Dupla;
import model.JogadorModel;
import model.MesaModel;

public class ControllerJogo {
    MesaModel jogo;
    Dupla d1, d2;

    public ControllerJogo(Dupla d1, Dupla d2) {
        this.d1 = d1;
        this.d2 = d2;
        
        jogo = new MesaModel(d1,d2);
        
        adicionarListenersTruco(d1, d2);
        adicionarListenersTruco(d2, d1);
        
        adicionarListenersCorrer(d1, d2);
        adicionarListenersCorrer(d2, d1);
        
        adicionarListenersAumentar(d1, d2);
        adicionarListenersAumentar(d2, d1);
        
        adicionarListenersAceitar(d1, d2);
        adicionarListenersAceitar(d2, d1);
        
        adicionarListenersCartas(jogo.getBaralho());
    }

    private void adicionarListenersTruco(Dupla d1, Dupla d2) {
        
        d1.getJ1().getPainelJogador().getTrucar().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                jogo.acaoTruco(d1, d2);
            }
        });
        
        d1.getJ2().getPainelJogador().getTrucar().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                jogo.acaoTruco(d1, d2);
            }
        });
    }

    
    
    private void adicionarListenersCorrer(Dupla d1, Dupla d2) {
        
        d1.getJ1().getPainelJogador().getCorrer().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                jogo.acaoCorreu(d1, d2);
            }
        });
        
        d1.getJ2().getPainelJogador().getCorrer().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                jogo.acaoCorreu(d1, d2);

            }
        });
    }

    
    
    
    private void adicionarListenersAumentar(Dupla d1, Dupla d2) {
        
        d1.getJ1().getPainelJogador().getAumentar().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                jogo.acaoAumentou(d1, d2);
            }
        });
        
        
        d1.getJ2().getPainelJogador().getAumentar().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                jogo.acaoAumentou(d1, d2);
            }
        });
        
    }

    
    
    private void adicionarListenersAceitar(Dupla d1, Dupla d2) {
        
        d1.getJ1().getPainelJogador().getAceitar().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                jogo.acaoAceitar(d1, d2);
            }
        });
        
        
        d1.getJ2().getPainelJogador().getAceitar().addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                jogo.acaoAceitar(d1, d2);
            }
        });
    }

    private void adicionarListenersCartas(ArrayList<CartaModel> baralho) {
        
        for(CartaModel c: baralho){
            c.getBotao().getBotao().addActionListener(new ActionListener(){
                public void actionPerformed(ActionEvent e){
                    jogo.acaoColocarNaMesa(c);
                    jogo.verificarVencedor();
                }
            });
        }
    }
    

    public MesaModel getJogo() {
        return jogo;
    }
    
    
}
