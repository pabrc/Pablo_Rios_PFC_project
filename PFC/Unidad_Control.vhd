library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;

entity Unidad_Control is
    Port ( d 				: in STD_LOGIC_VECTOR(1 downto 0);
		     pwm_conf		: in STD_LOGIC;
--			  cap_stop		: in STD_LOGIC;	
			  clk 			: in STD_LOGIC;
			  async_reset 	: in STD_LOGIC;
--           en_contador: out STD_LOGIC;
--           en_mux 		: out STD_LOGIC;
			  en_timer 		: out STD_LOGIC;
			  en_captura 	: out STD_LOGIC;
			  en_comparador: out STD_LOGIC;
			  en_pwm 		: out STD_LOGIC;
--			  en_mux_sin	: out STD_LOGIC;
--			  en_mux_tri	: out STD_LOGIC;
			  en_cont_35	: out STD_LOGIC;
			  en_pwm_1		: out STD_LOGIC;
			  en_ram_v		: out STD_LOGIC;
			  sync_reset 	: out STD_LOGIC
--			  estado 		: out STD_LOGIC_VECTOR (2 downto 0)
			  );
end Unidad_Control;

architecture Behavioral of Unidad_Control is

signal sreg : std_logic_vector (2 downto 0);-- declaracion señales internas
signal next_sreg : std_logic_vector (2 downto 0);
constant state0 : std_logic_vector (2 downto 0) :="000";
constant state1 : std_logic_vector (2 downto 0) :="001";
constant state2 : std_logic_vector (2 downto 0) :="010";
constant state3 : std_logic_vector (2 downto 0) :="011";
constant state4 : std_logic_vector (2 downto 0) :="100";
constant state5 : std_logic_vector (2 downto 0)	:="101";


begin

--estado<= sreg;

process (clk, async_reset, next_sreg, pwm_conf)

begin
	   if ( async_reset='1' ) then
         sreg <= STATE0;
      elsif clk='1' and clk'event then --Mirar esto si esta bien
         sreg <= next_sreg;
     end if;
end process;

process (sreg,d)

begin

 next_sreg<=state0;
 
 case sreg is

   when state0 => 							--Estado 0
	     if d="01" then
--				if cap_stop ='0' then
					next_sreg<= state1;
--				elsif cap_stop='1' then
--					next_sreg<= state5;
--				else
--					next_sreg<= state0;
--				end if;	
			elsif d ="10" then  
		     next_sreg<= state2;
		  
			elsif d = "11" then 
				if pwm_conf = '0'then
					next_sreg <= state3;
				elsif pwm_conf = '1' then
					next_sreg <= state4;
				else 
					next_sreg <= state0;
				end if;
				
			else 
				next_sreg <= state0;
			end if;
		  
when state1 => 								--Estado 1
		    if d="01" then 
			next_sreg <= state1;
		    else 
			next_sreg<= state0;
		end if;	
		 
				
 when state2 => 								--Estado 2
		    if d="10" then 
			next_sreg <= state2;
		    else 
			next_sreg<= state0;
		end if;	

when state3 => 								--Estado 3
	     	if d="11" and pwm_conf='0' then 
			next_sreg <= state3;
		    else 
			next_sreg<= state0;
		end if;	

when state4 => 								--Estado 4
	     	if d="11" and pwm_conf='1' then 
			next_sreg <= state4;
		    else 
			next_sreg<= state0;
		end if;	

--when state5 => 								--Estado 5
--		    if d="01" and cap_stop= '1' then 
--			next_sreg <= state5;
--		    else 
--			next_sreg<= state0;
--		end if;	
			 	
when others=>
			  next_sreg<= state0;
			  

end case;
						  
end process;

process (sreg) 

begin

	case sreg is
      when state0  =>  sync_reset <='1';    -- sync_reset
      when others => sync_reset<= '0'; 
	end case;  
  
  
-- case sreg is
--      when state1 | state2 |  state3 |  state4 |  state5 =>
--			en_contador <='1'; 										--en_contador
--      when others => en_contador<= '0'; 
-- end case;
-- 
--
--  case sreg is
--      when state1|  state2 |  state3 |  state4 |  state5 =>
--			en_mux <='1' ; 											--en_mux
--      when others =>en_mux<= '0';
--  end case;
--  
   case sreg is
      when state1 | state2   => 
			en_timer <='1' ; 											--en_timer
      when others => en_timer<= '0';
	end case;
  
	case sreg is
      when state1  => 
			en_captura <='1' ; 						
      when others => en_captura<= '0';							--en_captura
	end case;
  
	case sreg is
      when state2   => 
			en_comparador <='1' ; 									--en_comparador
      when others => en_comparador <= '0';
	end case;	
  
	case sreg is
      when state3 |  state4   => 
			en_pwm <='1' ; 	 
      when others => en_pwm<= '0';								--en_pwm
	end case;
  
	case sreg is
      when state4    => 
			en_pwm_1 <='1' ; 	 
      when others => en_pwm_1<= '0';								--en_pwm_1
	end case;
	
	case sreg is
      when state4    => 
			en_cont_35 <='1' ; 	 
      when others => en_cont_35<= '0';								--en_cont_35
	end case;
		
	case sreg is
      when state4    => 
			en_ram_v<='1' ; 	 
      when others => en_ram_v<= '0';								--en_ram_v
	end case;
			
		
		
	
--	case sreg is
--      when state4  => 
--			en_mux_sin <='1' ; 	 
--      when others => en_mux_sin<= '0';								--en_mux_sin
--	end case;
--	
--	case sreg is
--      when state5   => 
--			en_mux_tri <='1' ; 	 
--      when others => en_mux_tri<= '0';								--en_mux_tri
--	end case;
	
		
end process;
end Behavioral;

