package model;

import view.CartaView;

public class CartaModel {
    private final String valor;
    private final String naipe;
    private final CartaView botao;
    private boolean usada, jogada;
    private final int pontoAtribuido;

    public CartaModel(String valor, String naipe, int pontoAtribuido) {
        this.valor = valor;
        this.naipe = naipe;
        
        this.usada = false;
        this.jogada = false;
        this.pontoAtribuido = pontoAtribuido;
        
        botao = new CartaView(valor, naipe);
    }
    
    //SETTERS.

    public void setJogada(boolean jogada) {
        this.jogada = jogada;
    }
    
    public void setUsada(boolean usada) {
        this.usada = usada;
    }

    //GETTERS.
    public CartaView getBotao() {
        return botao;
    }

    public String getNaipe() {
        return naipe;
    }

    public String getValor() {
        return valor;
    }

    public int getPontoAtribuido() {
        return pontoAtribuido;
    }

    public boolean isUsada() {
        return usada;
    }

    public boolean isJogada() {
        return jogada;
    }
    
}
