package view;

import javax.swing.ImageIcon;
import javax.swing.JButton;

public class CartaView {
    
    private final JButton botao;
    private final String endereco;

    public CartaView(String valor, String naipe) {
        endereco = "images/"+valor+"_de_"+naipe+".png";
       
        botao = new JButton(new ImageIcon( getClass().getResource(endereco) ));
    }
    
    //GETTERS.
    
    public JButton getBotao() {
        return botao;
    }

    public String getEndereco() {
        return endereco;
    }
    
    //HABILITAR/DESABILITAR BOTAO.
    
    public void habilitarCarta() {
        botao.setEnabled(true);
    }
    
    public void desabilitarCarta() {
        botao.setEnabled(false);
    }
    
}
