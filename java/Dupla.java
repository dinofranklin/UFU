package model;

public class Dupla {
    private final JogadorModel j1, j2;
    private final int numeroDeDupla;
    private int quedasJogadas, quedasGanhas;
    private int pontos;
    private int rodadasJogadas, rodadasGanhas;
    
    public Dupla(JogadorModel j1, JogadorModel j2, int numeroDeDupla) {
        this.j1 = j1;
        this.j2 = j2;
        this.pontos = 0;
        this.quedasGanhas = 0;
        this.quedasJogadas = 0;
        this.rodadasGanhas = 0;
        this.rodadasJogadas = 0;
        this.numeroDeDupla = numeroDeDupla;
    }
    
    //FUNCOES GERAIS
    
    
    public boolean jogadorPertence(JogadorModel j){
        return j == j1 || j == j2;
    }
    
    public void fimDeJogo(){
        rodadasGanhas = 0;
        rodadasJogadas = 0;
        pontos = 0;
    }
    
    public void fimDaQueda(boolean venci, int pontosGanhos){
        if(venci) quedasGanhas++;
        quedasJogadas++;
        
        rodadasGanhas = 0;
        rodadasJogadas = 0;
        
        pontos += pontosGanhos;
    }
    
    public void fimDaRodada(boolean venci){
        if(venci) rodadasGanhas++;
        rodadasJogadas++;
        
        //System.out.println("FIM DA RODADA PRA DUPLA");
        j1.excluirJogadas();
        j2.excluirJogadas();
    }
    
    
    public void limparInterface(){
        j1.entregarCartas();
        j2.entregarCartas();
    }
    
    
    public int maiorCartaJogada(){
        int ptj1 = j1.maiorPontoAtribuido();
        int ptj2 = j2.maiorPontoAtribuido();
        
        if(ptj1 > ptj2) return ptj1;
        else return ptj2;
    }
    
    
    public void trucaramAfavor(){
        j1.trucaramAfavor();
        j2.trucaramAfavor();
    }
    
    
    public void trucaramContra(int pontos){
        j1.trucaramContra(pontos);
        j2.trucaramContra(pontos);
    }
    
    
    public String imprime(){
        String texto = "Dupla " + numeroDeDupla + "\n";
        texto += "    Jogador 1: " + j1.getNome() + "\n";
        texto += "    Jogador 2: " + j2.getNome() + "\n";
        texto += "    Q.J.: " + quedasJogadas + " Q.G.: " + quedasGanhas + "\n";
        return texto;
    }
    
    //GETTERS

    public JogadorModel getJ1() {
        return j1;
    }

    public JogadorModel getJ2() {
        return j2;
    }

    public int getQuedasGanhas() {
        return quedasGanhas;
    }

    public int getQuedasJogadas() {
        return quedasJogadas;
    }

    public int getRodadasGanhas() {
        return rodadasGanhas;
    }

    public int getRodadasJogadas() {
        return rodadasJogadas;
    }

    public int getPontos() {
        return pontos;
    }

    public int getNumeroDeDupla() {
        return numeroDeDupla;
    }
   
      
}
