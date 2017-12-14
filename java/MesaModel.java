package model;

import java.util.ArrayList;
import java.util.Random;
import javax.swing.JOptionPane;
import view.MesaView;

public class MesaModel {
    //VARIAVEIS DA MESA
    private ArrayList<CartaModel> baralho;
    private final Dupla d1, d2;
    private MesaView mesa;
    
    //VARIAVEIS DE CONTROLE.
    private CartaModel cm1, cm2, cm3, cm4; //CARTAS JOGADAS.
    private int pontosDeTruco, pontosApostados;
    private int numeroDeRodada;
    private int cartasNaMesa, maiorValorNaMesa;
    private boolean jogadorJogou;
    private JogadorModel jogadorAtual;
    private boolean houveTruco;

    public MesaModel(Dupla d1, Dupla d2) {
        this.d1 = d1;
        this.d2 = d2;
        
        baralho = new ArrayList<> ();
        mesa = new MesaView();
        cm1 = cm2 = cm3 = cm4 = null;
        pontosDeTruco = 0;
        maiorValorNaMesa = 0;
        numeroDeRodada = 1;
        pontosApostados = 1;
        cartasNaMesa = 0;
        jogadorAtual = null;
        houveTruco = false;
        
        System.out.println("INICIALIZEI SHOW");
        gerarBaralho();
        System.out.println("GEREI SHOW");
        distribuirBaralho();
        System.out.println("DISTRIBUI");
        mesa.fazerMesa(d1.getJ1().getPainelJogador(), d1.getJ2().getPainelJogador(), d2.getJ1().getPainelJogador(), d2.getJ2().getPainelJogador());
        mesa.atualizarPlacar(d1.getNumeroDeDupla(), d2.getNumeroDeDupla(), d1.getPontos(), d2.getPontos(), pontosApostados);
        jogadorAtual = d1.getJ1();
        desabilitarExceto(jogadorAtual);
    }
    
    
    //FUNCOES GERAL DE JOGO E FLUXO
    
    public void voltarRodada(){
        if(!jogadorJogou){
            desabilitarExceto(jogadorAtual);
        }
        else{
            jogadorAtual = proximoJogador(jogadorAtual);
            desabilitarExceto(jogadorAtual);
        }
    }
    
    
    public void proximaRodada(Dupla d){
        Dupla vencedora = d;
        imprimirResultado(vencedora, "rodada");
                    
        System.out.println("RODADA " + numeroDeRodada);
        if(numeroDeRodada == 3){
            int ptd1, ptd2;
            ptd1 = d1.getRodadasGanhas();
            ptd2 = d2.getRodadasGanhas();
            
            System.out.println("ACABOU A QUEDA");
            
            if(ptd1 == 2 || (ptd1 == 1 && ptd2 == 0)){
                d1.fimDaQueda(true, pontosApostados);
                d2.fimDaQueda(false, 0);
                vencedora = d1;
            } 
            else if(ptd2 == 2 || (ptd2 == 1 && ptd1 == 0)){
                d2.fimDaQueda(true, pontosApostados);
                d1.fimDaQueda(false, 0);
                vencedora = d2;
            }
            else{
                System.out.println("CRITERIO DE DESEMPATE");
            }
            mesa.atualizarPlacar(d1.getNumeroDeDupla(), d2.getNumeroDeDupla(), d1.getPontos(), d2.getPontos(), pontosApostados);
            imprimirResultado(vencedora, "queda");
            verificarGanhadorJogo();
            finalizarQueda();;
        }
        
        
        numeroDeRodada++;
        cm1 = cm2 = cm3 = cm4 = null;
        maiorValorNaMesa = 0;
        cartasNaMesa = 0;
        mesa.limparCartas();
        
        if(vencedora.jogadorPertence(jogadorAtual)){
            desabilitarExceto(jogadorAtual);
        }
        else{
            jogadorAtual = jogadorAnterior(jogadorAtual);
            desabilitarExceto(jogadorAtual);
        }
        jogadorJogou = false;
    }
    
    public void verificarGanhadorJogo(){
        Dupla vencedora = null;
        if(d1.getPontos() >= 12) vencedora = d1;
        else if(d1.getPontos() >= 12) vencedora = d2;
        
        if(vencedora == null) return;
        imprimirResultado(vencedora, "jogo");
        d1.fimDeJogo();
        d2.fimDeJogo();
        
        mesa.getJanela().setVisible(false);
        mesa.getJanela().dispose();
    }
    
    
    public void finalizarQueda(){
        numeroDeRodada = 0;
        pontosApostados = 1;
        pontosDeTruco = 1;
        houveTruco = false;
        
        d1.getJ1().entregarCartas();
        d1.getJ2().entregarCartas();
        d2.getJ1().entregarCartas();
        d2.getJ2().entregarCartas();
        
        for(CartaModel c : baralho){
            c.setJogada(false);
            c.setUsada(false);
        }
        
        distribuirBaralho();
    }
    
    public void imprimirResultado(Dupla d, String tipo){
        String s = "";
        s += "Parabens " + d.getJ1().getNome() + " e " + d.getJ2().getNome() + "\nVoces ganaharam ";
        if(tipo.equals("jogo")) s+= "o jogo!\n";
        else s += "a " + tipo + "!\n";
        
        JOptionPane.showMessageDialog(null, s);
    }
    
    public void verificarVencedor(){
        if(cartasNaMesa == 4){
            ;
            int maiorD1, maiorD2;
            maiorD1 = d1.maiorCartaJogada();
            maiorD2 = d2.maiorCartaJogada();
            
            System.out.println("MAIORMESA = " +maiorValorNaMesa + " D1 = " + maiorD1 + " D2 = " + maiorD2);
            
            if(maiorD1 == maiorValorNaMesa && maiorD2 == maiorValorNaMesa){
                d1.fimDaRodada(false);
                d2.fimDaRodada(false);
                proximaRodada(d1);
            }
            else if(maiorD1 == maiorValorNaMesa){
                d1.fimDaRodada(true);
                d2.fimDaRodada(false);
                proximaRodada(d1);
            }
            else if(maiorD2 == maiorValorNaMesa){
                d1.fimDaRodada(false);
                d2.fimDaRodada(true);
                proximaRodada(d2);
            }
            else System.out.println("DEU RUIM");
        }
        else{
            voltarRodada();
        }
    }
    
    
    public void verificarVencedor(Dupla d){
        
        System.out.println("ALGUEM CORREU E VENCEU");
        d.fimDaRodada(true);
        if(d == d1) d2.fimDaRodada(false);
        else if(d == d2) d1.fimDaRodada(false);
        
        proximaRodada(d);
    }
    
    
    private JogadorModel proximoJogador(JogadorModel j){
        if(j == d1.getJ1()) return d2.getJ1();
        if(j == d2.getJ1()) return d1.getJ2();
        if(j == d1.getJ2()) return d2.getJ2();
        if(j == d2.getJ2()) return d1.getJ1();
        return null;
    }
    
    private JogadorModel jogadorAnterior(JogadorModel j){
        if(j == d1.getJ1()) return d2.getJ2();
        if(j == d2.getJ2()) return d1.getJ2();
        if(j == d1.getJ2()) return d2.getJ1();
        if(j == d2.getJ1()) return d1.getJ1();
        return null;
    }
    
    private void desabilitarExceto(JogadorModel j){
        System.out.println("Desabilitando");
        j.habilitarJogada(houveTruco, pontosApostados);
        if(j != d1.getJ1()) d1.getJ1().desabilitarJogada(houveTruco, pontosApostados);
        if(j != d1.getJ2()) d1.getJ2().desabilitarJogada(houveTruco, pontosApostados);
        if(j != d2.getJ1()) d2.getJ1().desabilitarJogada(houveTruco, pontosApostados);
        if(j != d2.getJ2()) d2.getJ2().desabilitarJogada(houveTruco, pontosApostados);
    }
    
    //ACOES TOMADAS PELOS BOTOES.
    
    
    public void acaoColocarNaMesa(CartaModel c){
        jogadorJogou = true;
        
        if(!jogadorAtual.buscarCarta(c)) System.out.println("ALGO ERRADO");
        if(c.getPontoAtribuido() > maiorValorNaMesa) maiorValorNaMesa = c.getPontoAtribuido();
        
        if(cm1 == null) cm1 = c;
        if(cm2 == null) cm2 = c;
        if(cm3 == null) cm3 = c;
        if(cm4 == null) cm4 = c;
        
        ++cartasNaMesa;
        jogadorAtual.jogarCarta(c);
        mesa.atualizaCentro(c.getBotao());
    }
    
    
    public void acaoAumentou(Dupla desafiou, Dupla desafiado){
        pontosApostados = pontosDeTruco;
        pontosDeTruco += 3;
        
        System.out.println("AUMENTEI AGORA " + pontosApostados);
        mesa.atualizarPlacar(d1.getNumeroDeDupla(), d2.getNumeroDeDupla(), d1.getPontos(), d2.getPontos(), pontosApostados);
        
        desafiou.trucaramAfavor();
        desafiado.trucaramContra(pontosDeTruco);
        
    }
    
    
    public void acaoAceitar(Dupla dp1, Dupla dp2){
        pontosApostados = pontosDeTruco;
        System.out.println("ACEITEI AGORA " + pontosApostados);
        mesa.atualizarPlacar(d1.getNumeroDeDupla(), d2.getNumeroDeDupla(), d1.getPontos(), d2.getPontos(), pontosApostados);
        voltarRodada();
    }
    
    
    public void acaoCorreu(Dupla correu, Dupla vencedora){
        verificarVencedor(vencedora);
    }
    
    
    public void acaoTruco(Dupla trucou, Dupla trucado){
        if(houveTruco) System.out.println("TEM COISA ERRADA!");
        
        houveTruco = true;
        pontosDeTruco = 3;
        
        System.out.println("ALGUEM TRUCOU");
        trucou.trucaramAfavor();
        trucado.trucaramContra(pontosDeTruco);
        
    }
    
    
    //FUNCOES PARA GERAR BARALHO E DESTRIBUIR SUAS CARTAS.
    
    
    private void distribuirBaralho(){
        distribuirCartas(d1.getJ1());
        distribuirCartas(d1.getJ2());
        distribuirCartas(d2.getJ1());
        distribuirCartas(d2.getJ2());
    }
    
    
    private void distribuirCartas(JogadorModel j){
        int r;
        
        for(int i=0; i<3; ++i){
            while(true){
                r = new Random().nextInt(40);
                if(baralho.get(r).isUsada()) continue;
                j.setCarta(baralho.get(r));
                break;
            }
        }
        
    }
    
    
    private void gerarBaralho(){
        String[] naipes = {"paus", "ouros", "copas", "espadas"};
        String[] valores = {"as","2","3","4","5","6","7","valete","dama","rei"};
        
        for(int i=0; i<valores.length; ++i){
            for(int j=0; j<naipes.length; ++j){
                baralho.add(new CartaModel(valores[i], naipes[j], valorPonto(valores[i], naipes[j])));
            }
        }
    }
    
    private int valorPonto(String valor, String naipe){
        if("4".equals(valor) && "paus".equals(naipe)) return 14;
        if("7".equals(valor) && "copas".equals(naipe)) return 13;
        if("as".equals(valor) && "espadas".equals(naipe)) return 12;
        if("7".equals(valor) && "ouros".equals(naipe)) return 11;
        if("3".equals(valor)) return 10;
        if("2".equals(valor)) return 9;
        if("as".equals(valor)) return 8;
        if("rei".equals(valor)) return 7;
        if("valete".equals(valor)) return 6;
        if("dama".equals(valor)) return 5;
        if("7".equals(valor)) return 4;
        if("6".equals(valor)) return 3;
        if("5".equals(valor)) return 2;
        if("4".equals(valor)) return 1;
        return 0;
    }
    
    //GETTER

    public ArrayList<CartaModel> getBaralho() {
        return baralho;
    }

    public MesaView getMesa() {
        return mesa;
    }
    
}
