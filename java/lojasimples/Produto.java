package loja;

public class Produto {
    private String descricao;
    private int quantidadeEstoque;
    private double precoUnitario;
    
    public Produto(String desc, int qtd, double preco){
        this.descricao = desc;
        this.quantidadeEstoque = qtd;
        this.precoUnitario = preco;
    }
    
    public String retornaNome(){
        return this.descricao;
    }
    
    public int retornaQuantidade(){
        return this.quantidadeEstoque;
    }
    
    public double retornaPreco(){
        return this.precoUnitario;
    }
    
    public void venderProduto(int n){
        this.quantidadeEstoque -= n;
    }
    
    public void reporProduto(int n){
        this.quantidadeEstoque += n;
    }
}
