package model;

import view.JogadorView;

public class JogadorModel {
    
    private final String nome;
    private CartaModel c1, c2, c3;
    JogadorView painelJogador;

    public JogadorModel(String nome) {
        this.nome = nome;
        
        painelJogador = new JogadorView(nome);
    }

    //GETTERS.
    
    public String getNome() {
        return nome;
    }

    public JogadorView getPainelJogador() {
        return painelJogador;
    }
    
    //FUNCOES GERAIS PARA CARTAS.
    public void setCarta(CartaModel c){
        if(c1 == null) c1 = c;
        else if(c2 == null) c2 = c;
        else if(c3 == null) c3 = c;
        else return; //FALHOU
        
        c.setUsada(true);
        painelJogador.setCarta(c.getBotao());
    }
    
    public void jogarCarta(CartaModel c){
        //System.out.println("JOGUEI CARTA " + nome);
        
        c.setJogada(true);
        painelJogador.removerCarta(c.getBotao());
    }
    
    
    public void entregarCartas(){
        painelJogador.limparCartas();
        
        c1 = c2 = c3 = null;
    }
    
    public void desabilitarCartas(){
        //System.out.println("DESABILITANDO CARTAS DO JOGADOR " + nome);
        if(c1 != null) c1.getBotao().desabilitarCarta();
        if(c2 != null) c2.getBotao().desabilitarCarta();
        if(c3 != null) c3.getBotao().desabilitarCarta();
    }
    
    public void habilitarCartas(){
        //System.out.println("HABILITANDO CARTAS DO JOGADOR " + nome);
        if(c1 != null) c1.getBotao().habilitarCarta();
        if(c2 != null) c2.getBotao().habilitarCarta();
        if(c3 != null) c3.getBotao().habilitarCarta();
    }
    
    public boolean buscarCarta(CartaModel c){
        return c == c1 || c == c2 || c == c3;
    }
    
    public boolean buscarCartaPontos(int pontos){
        if(c1 != null && c1.isJogada() == true && c1.getPontoAtribuido() == pontos) return true;
        if(c2 != null && c2.isJogada() == true && c2.getPontoAtribuido() == pontos) return true;
        return c3 != null && c3.isJogada() == true && c3.getPontoAtribuido() == pontos;
    }
    
    public int maiorPontoAtribuido(){
        int max = -1;
        if(c1 != null && c1.isJogada() == true && c1.getPontoAtribuido() > max) max = c1.getPontoAtribuido();
        if(c2 != null && c2.isJogada() == true && c2.getPontoAtribuido() > max) max = c2.getPontoAtribuido();
        if(c3 != null && c3.isJogada() == true && c3.getPontoAtribuido() > max) max = c3.getPontoAtribuido();
        return max;
    }
    
    
    public void excluirJogadas(){
        if(c1 != null && c1.isJogada()) c1 = null;
        if(c2 != null && c2.isJogada()) c2 = null;
        if(c3 != null && c3.isJogada()) c3 = null;
    }
    
    //FUNCOES GERAIS PARA HABILITAR/DESABILITAR BOTOES.
    
    public void habilitarJogada(boolean houveTruco, int pontosApostados){
        habilitarCartas();
        painelJogador.desabilitarAceitar();
        painelJogador.desabilitarCorrer();
        
        //CASO 9 PONTOS ESTAO APOSTADOS NAO SE PODE MAIS TRUCAR NEM AUMENTAR.
        if(pontosApostados >= 9){
            painelJogador.desabilitarAumentar();
            painelJogador.desabilitarTruco();
        }
        
        //SE JA HOUVER TRUCADO ENTAO SÓ SE PODE AUMENTAR.
        else if(houveTruco){
            painelJogador.habilitarAumentar();
            painelJogador.desabilitarTruco();
        }
        //DO CONTRARIO SE PODE TRUCAR MAS NAO AUMENTAR.
        else{
            painelJogador.habilitarTruco();
            painelJogador.desabilitarAumentar();
        }
    }
    
    public void desabilitarJogada(boolean houveTruco, int pontosApostados){
        desabilitarCartas();
        painelJogador.desabilitarAceitar();
        painelJogador.desabilitarCorrer();
        
        //CASO 9 PONTOS ESTAO APOSTADOS NAO SE PODE MAIS TRUCAR NEM AUMENTAR.
        if(pontosApostados >= 9){
            painelJogador.desabilitarAumentar();
            painelJogador.desabilitarTruco();
        }
        
        //SE JA HOUVER TRUCADO ENTAO SÓ SE PODE AUMENTAR.
        else if(houveTruco){
            painelJogador.habilitarAumentar();
            painelJogador.desabilitarTruco();
        }
        //DO CONTRARIO SE PODE TRUCAR MAS NAO AUMENTAR.
        else{
            painelJogador.habilitarTruco();
            painelJogador.desabilitarAumentar();
        }
    }
    
    public void trucaramContra(int pontosApostados){
        desabilitarCartas();
        painelJogador.desabilitarTruco();
        painelJogador.habilitarAceitar();
        painelJogador.habilitarCorrer();
        if(pontosApostados >= 9){
            painelJogador.desabilitarAumentar();
        }
        else{
            painelJogador.habilitarAumentar();
        }
    }
    
    public void trucaramAfavor(){
        desabilitarCartas();
        painelJogador.desabilitarAceitar();
        painelJogador.desabilitarAumentar();
        painelJogador.desabilitarTruco();
        painelJogador.desabilitarCorrer();
    }
}
