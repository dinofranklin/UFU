package jogodedado;

public class Jogador {
    private String nome;
    private int pontos;
    
    public Jogador(String name){
        this.nome = name;
        this.pontos = 0;
    }
    
    public int retornaPontos(){
        return this.pontos;
    }
    
    public String retornaNome(){
        return this.nome;
    }
    
    public int rolarDado(){
        int x = ((int) (Math.random() * 6) + 1);
        this.pontos += x;
        return x;
    }
}
