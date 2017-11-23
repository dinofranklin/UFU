package calculadora;

public class Eval {
    int ans;
    String s;
    
    public Eval(String s){
        this.s = s;
        ans = 0;
    }
    
    public boolean evaluate(){
        int n, ac = 0;
        char opcode = '?';
        String sb = new String();
        if(sintax_check() == false) return false;
        
        for(int i=0; i<s.length(); ++i){
            
            if(s.charAt(i) <= '9' && s.charAt(i) >= '0'){
                sb += s.charAt(i);
            }
            else if(opcode != '?'){
                n = Integer.parseInt(sb);
                if(opcode == '+'){
                    ac += n;
                }
                else if(opcode == '-'){
                    ac -= n;
                }
                else if(opcode == '*'){
                    ac *= n;
                }
                else if(opcode == '/'){
                    ac /= n;
                }
                sb = "";
                opcode = s.charAt(i);
            }
            else if(opcode == '?'){
                ac = Integer.parseInt(sb);
                sb = "";
                opcode = s.charAt(i);
            }
            else{
                return false;
            }
        }
        if(sb.length() > 0){
            if(opcode == '+') ac += Integer.parseInt(sb);
            else if(opcode == '-') ac -= Integer.parseInt(sb);
            else if(opcode == '*') ac *= Integer.parseInt(sb);
            else if(opcode == '/') ac /= Integer.parseInt(sb);
        }
        
        this.ans = ac;
        return true;
    }
    
    public int getAns(){
        return ans;
    }
    
    private boolean sintax_check(){
        boolean num = false;
        for(int i=0; i<s.length(); ++i){
            if(s.charAt(i) >= '0' || s.charAt(i) <= '9'){
                //System.out.println("eh num " + s.charAt(i) + " " + num);
                num = true;
            }
            else if("+-\\*".indexOf(s.charAt(i)) != -1){
                //System.out.println("eh sig " + s.charAt(i) + " " + num);
                if(num == false) return false;
                num = false;
            }
            else{
                //System.out.println("deu ruim");
                return false;
            }
        }
        return true;
    }
}
