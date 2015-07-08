library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


entity Unidad_Operativa is
    Port (async_reset 	: in STD_LOGIC;
			 clk 				: in STD_LOGIC;
			 clk_100			: in STD_LOGIC;	
			 en_mux 			: in STD_LOGIC;
			 direc 			: in STD_LOGIC_VECTOR (3 downto 0);  -- entrada del mux
			 direc_ram		: in STD_LOGIC_VECTOR (5 downto 0); -- direccion de escritura RAM_valores
			 sel_salida 	: in STD_LOGIC_VECTOR (3 downto 0); --seleciona si leo el BD0,BD1... o el timer
			 datos 			: in STD_LOGIC_VECTOR (31 downto 0); -- entrada de datos
			 wr 				: in STD_LOGIC; -- Activacion escritura			 
			 captura_0 		: in STD_LOGIC; -- Flanco aqui y captura0.
			 captura_1 		: in STD_LOGIC; -- Flanco aqui y captura1.
			 captura_2 		: in STD_LOGIC; -- Flanco aqui y captura2.
			 captura_3 		: in STD_LOGIC; -- Flanco aqui y captura3.
			 captura_4 		: in STD_LOGIC; -- Flanco aqui y captura4.
			 pwm_out 		: out STD_LOGIC; -- salida de pwm
			 compara_int_0 : out STD_LOGIC; --interrupcion de la comparacion. Avisa al micro
			 compara_out_0 : out STD_LOGIC;	--salida de la comparacion
			 compara_int_1 : out STD_LOGIC; --interrupcion de la comparacion. Avisa al micro
			 compara_out_1 : out STD_LOGIC;	--salida de la comparacion
			 compara_int_2 : out STD_LOGIC; --interrupcion de la comparacion. Avisa al micro
			 compara_out_2 : out STD_LOGIC;	--salida de la comparacion
			 compara_int_3 : out STD_LOGIC; --interrupcion de la comparacion. Avisa al micro
			 compara_out_3 : out STD_LOGIC;	--salida de la comparacion
			 compara_int_4 : out STD_LOGIC; --interrupcion de la comparacion. Avisa al micro
			 compara_out_4 : out STD_LOGIC;	--salida de la comparacion
			 captura_int_0 : out STD_LOGIC; -- interrupcion de la captura. Avisa al micro
			 captura_int_1 : out STD_LOGIC; -- interrupcion de la captura. Avisa al micro
			 captura_int_2 : out STD_LOGIC; -- interrupcion de la captura. Avisa al micro
			 captura_int_3 : out STD_LOGIC; -- interrupcion de la captura. Avisa al micro
			 captura_int_4 : out STD_LOGIC; -- interrupcion de la captura. Avisa al micro
		--	 captura_dato0 : out STD_LOGIC_VECTOR (31 downto 0);
	--		 captura_dato1 : out STD_LOGIC_VECTOR (31 downto 0);
--			 valor_timer 	: out STD_LOGIC_VECTOR (31 downto 0); --Dato salida captura
			 datos_out		: out STD_LOGIC_VECTOR (31 downto 0) -- Dato de lectura de BD0,BD1...timer
		--	 estado 			: out STD_LOGIC_VECTOR (2 downto 0 )
			);
end Unidad_Operativa;

architecture Behavioral of Unidad_Operativa is

component timer
	port(
		async_reset	: in  STD_LOGIC;
		sync_reset 	: in  STD_LOGIC;
      en 			: in  STD_LOGIC;
      clk			: in  STD_LOGIC;
      load		 	: in STD_LOGIC;
      d			 	: in  STD_LOGIC_VECTOR(31 downto 0);
      q			 	: out  STD_LOGIC_VECTOR(31 downto 0));
end component;
	 

component Unidad_Control
	port(
			  d 				: in  STD_LOGIC_VECTOR(1 downto 0);
			  pwm_conf		: in STD_LOGIC;
--			  cap_stop		: in STD_LOGIC;	
			  clk 			: in  STD_LOGIC;
			  async_reset 	: in  STD_LOGIC;
--         en_contador 	: out  STD_LOGIC;
--         en_mux 		: out  STD_LOGIC;
			  en_timer 		: out  STD_LOGIC;
			  en_captura 	: out  STD_LOGIC;
			  en_comparador: out  STD_LOGIC;
			  en_pwm 		: out  STD_LOGIC;
--			  en_mux_sin	: out STD_LOGIC;
--			  en_mux_tri	: out STD_LOGIC;
			  en_cont_35	: out STD_LOGIC;
			  en_pwm_1		: out STD_LOGIC;
			  en_ram_v		: out STD_LOGIC;
			  sync_reset 	: out STD_LOGIC);
--			  estado 		: out STD_LOGIC_VECTOR (2 downto 0));
end component;

component R_Conf 
port(
			  async_reset 		 : in STD_LOGIC;
           en  				 : in STD_LOGIC;
           clk 				 : in STD_LOGIC;
			  in_captura_0 	 : in STD_LOGIC;
			  in_captura_1 	 : in STD_LOGIC;
			  in_captura_2 	 : in STD_LOGIC;
			  in_captura_3 	 : in STD_LOGIC;
			  in_captura_4 	 : in STD_LOGIC;
			  in_comparacion_0 : in STD_LOGIC;
			  in_comparacion_1 : in STD_LOGIC;
			  in_comparacion_2 : in STD_LOGIC;
			  in_comparacion_3 : in STD_LOGIC;
			  in_comparacion_4 : in STD_LOGIC;
           d 					 : in STD_LOGIC_VECTOR (15 downto 0);
           sync_reset 		 : in STD_LOGIC;
			  q  					 : out STD_LOGIC_VECTOR (15 downto 0);
           captura_0 		 : out STD_LOGIC;
			  captura_1 		 : out STD_LOGIC;
			  captura_2 		 : out STD_LOGIC;
			  captura_3 		 : out STD_LOGIC;
			  captura_4 		 : out STD_LOGIC;
			  comparacion_0 	 : out STD_LOGIC;
			  comparacion_1 	 : out STD_LOGIC;
			  comparacion_2 	 : out STD_LOGIC;
			  comparacion_3 	 : out STD_LOGIC;
			  comparacion_4 	 : out STD_LOGIC);
end component;
	
	
component Detector_Flancos is
    Port ( clk 					: in STD_LOGIC;
           reset 					: in STD_LOGIC;
           input 					: in STD_LOGIC;
           out_falling_edge : out STD_LOGIC;
           out_rising_edge 	: out STD_LOGIC);
end component;

	
component reg_captura
	port(	async_reset	: in STD_LOGIC;
			sync_reset 	: in STD_LOGIC;
			en 			: in STD_LOGIC;
			lec 			: in STD_LOGIC;
			clk 			: in STD_LOGIC;
			d 				: in STD_LOGIC_VECTOR(31 downto 0);
			captura 		: in STD_LOGIC;
			sel_r 		: out STD_LOGIC;		
			q 				: out STD_LOGIC_VECTOR(31 downto 0);
			int_salida 	: out STD_LOGIC);
	end component;
	
	component Comparador is
    Port ( async_reset 	: in STD_LOGIC;
			  sync_reset 	: in STD_LOGIC;
			  en 				: in STD_LOGIC;
           dato 			: in STD_LOGIC_VECTOR (31 downto 0);
			  timer 			: in STD_LOGIC_VECTOR (31 downto 0);
			  compara_out 	: out STD_LOGIC;
           compara_int 	: out STD_LOGIC);
	end component;
	
component pwm is
    Port ( 
			  async_reset 	: in  STD_LOGIC;
			  sync_reset 	: in  STD_LOGIC;
           en 				: in  STD_LOGIC;
           clk 			: in  STD_LOGIC;
           ton 			: in  STD_LOGIC_VECTOR(31 downto 0);
			  per 			: in  STD_LOGIC_VECTOR(31 downto 0);
			  q 				: out  STD_LOGIC);
end component;


--component Contador is
--    Port ( en 				: in  STD_LOGIC;
--           async_reset 	: in  STD_LOGIC;
--           sync_reset 	: in  STD_LOGIC;
--           clk 			: in  STD_LOGIC;
--           q 				: out  STD_LOGIC_VECTOR(3 downto 0));
--end component;


--component Mux_clk is
--    Port ( async_reset	: in  STD_LOGIC;
--           en 				: in  STD_LOGIC;
--			  in0				: in  STD_LOGIC;
--			  in1				: in  STD_LOGIC;
--			  in2				: in  STD_LOGIC;
--			  in3				: in  STD_LOGIC;
--			  in4 			: in  STD_LOGIC;
--           sel 			: in  STD_LOGIC_VECTOR (2 downto 0);
--           sync_reset 	: in  STD_LOGIC;
--           q 				: out  STD_LOGIC);
--end component;
	


component Biestable_D is
   Port (async_reset : in  STD_LOGIC;
         en 			: in  STD_LOGIC;
         clk 			: in  STD_LOGIC;
         d 				: in  STD_LOGIC_VECTOR (31 downto 0);
         sync_reset 	: in  STD_LOGIC;
         q 				: out  STD_LOGIC_VECTOR (31 downto 0));
end component;


component and_2 is
		Port (
			  a : in  STD_LOGIC;
           b : in  STD_LOGIC;
           c : out  STD_LOGIC);
end component;


component Mux_in is
    Port ( async_reset	: in  STD_LOGIC;
           en 				: in  STD_LOGIC;
           sel 				: in  STD_LOGIC_VECTOR (3 downto 0);
           sync_reset 	: in  STD_LOGIC;
           q 				: out  STD_LOGIC_VECTOR (11 downto 0));
end component;

component multiplex_salida is
		Port ( 
			  async_reset 	: in  STD_LOGIC;
           en 				: in  STD_LOGIC;
			  in0 			: in  STD_LOGIC_VECTOR (31 downto 0);
			  in1 			: in  STD_LOGIC_VECTOR (31 downto 0);
			  in2 			: in  STD_LOGIC_VECTOR (31 downto 0);
			  in3 			: in  STD_LOGIC_VECTOR (31 downto 0);
			  in4 			: in  STD_LOGIC_VECTOR (31 downto 0);
			  in5 			: in  STD_LOGIC_VECTOR (31 downto 0);
			  in6 			: in  STD_LOGIC_VECTOR (31 downto 0);
			  in7 			: in  STD_LOGIC_VECTOR (31 downto 0);
			  in8 			: in  STD_LOGIC_VECTOR (31 downto 0);
			  in9 			: in  STD_LOGIC_VECTOR (31 downto 0);
			  in10 			: in  STD_LOGIC_VECTOR (31 downto 0);
			  in11 			: in  STD_LOGIC_VECTOR (31 downto 0);
			  in12 			: in  STD_LOGIC_VECTOR (31 downto 0);
			  in13 			: in  STD_LOGIC_VECTOR (31 downto 0);
			  in14 			: in  STD_LOGIC_VECTOR (31 downto 0);
           sel 			: in  STD_LOGIC_VECTOR (3 downto 0);
           sync_reset 	: in  STD_LOGIC;
           q 				: out  STD_LOGIC_VECTOR(31 downto 0));
end component;

-------------------------------------

Component Retardador is
    Port ( async_reset 	: in  STD_LOGIC;
           sync_reset	: in  STD_LOGIC;
           clk 			: in  STD_LOGIC;
			  entrada		: in STD_LOGIC;
           q 				: out  STD_LOGIC );
end component;
--------------------------------------

Component ram_valores is
    port (CLK  : in std_logic;
          WE   : in std_logic;
          EN   : in std_logic;
          ADDR : in std_logic_vector(5 downto 0);
          DI   : in std_logic_vector(31 downto 0);
          DO   : out std_logic_vector(31 downto 0));
end component;


--
--component mux_tri is
--		PORT(	sel   	: IN std_logic_vector(5 DOWNTO 0); 
--				en	  		: IN std_logic;
--            salida 	: OUT std_logic_vector(31 DOWNTO 0));
--end component;
--
--component mux_sin is
--		PORT(	sel   	: IN std_logic_vector(5 DOWNTO 0); 
--				en	  		: IN std_logic;
--            salida 	: OUT std_logic_vector(31 DOWNTO 0));
--end component;

component Cont_35 is
    Port ( en 				: in  STD_LOGIC;
           async_reset 	: in  STD_LOGIC;
           sync_reset 	: in  STD_LOGIC;
           clk 			: in  STD_LOGIC;
           q 				: out  STD_LOGIC_VECTOR(5 downto 0));
end component;

component Mux2_32 is
    Port ( async_reset	: in  STD_LOGIC;
           a 				: in  STD_LOGIC_VECTOR (31 downto 0);
           b 				: in  STD_LOGIC_VECTOR (31 downto 0);
			  sel 			: in  STD_LOGIC;
           q 				: out  STD_LOGIC_VECTOR (31 downto 0));
end component;

component Mux2_6 is
    Port ( async_reset 	: in  STD_LOGIC;
           a 				: in  STD_LOGIC_VECTOR (5 downto 0);
           b 				: in  STD_LOGIC_VECTOR (5 downto 0);
			  sel 			: in  STD_LOGIC;
           q 				: out  STD_LOGIC_VECTOR (5 downto 0));
end component;

component or_2 is
		Port (a : in  STD_LOGIC;
				b : in  STD_LOGIC;
				c : out  STD_LOGIC);
end component;


component Registro_32 is
    port(CLK 	: in std_logic;
			CLR	: in std_logic;
			EN		: in std_logic;
			EN_CAP: in std_logic;
         D 		: in std_logic_vector(31 downto 0);
			SDETR	: out std_logic;
         Q 		: out std_logic_vector(31 downto 0));
end component;

component inv is
    port(E 	: in std_logic;
         Q 	: out std_logic);
end component;


component xor_2 is
    Port ( a : in  STD_LOGIC;
           b : in  STD_LOGIC;
           c : out  STD_LOGIC);
end component;

component det_r is
    Port ( a : in  STD_LOGIC;
           b : in  STD_LOGIC;
           c : out  STD_LOGIC);
end component;



------------------------------------------------------------
----------- DECLARACION DE SEÑALES DE CONEXION -------------
------------------------------------------------------------

signal en0,en0_1,en1,en1_1,en2,en2_1,en3,en3_1,en4,en4_1,en5,en5_1,en6,en6_1,en7,en7_1,en8,en8_1,en9,en9_1,en10,en10_1,en11 : std_logic;
signal captur0,captur1,captur2,captur3,captur4,f2,f4,f8,f16,eram_valores,wr_ram,eram_v: std_logic;
signal selecion,captu0,cpt0,captu1,captu2,captu3,captu4,compa0,compa1,compa2,compa3,compa4,sel0,sel1,sel2,uc0,uc1,ecom,ecap,epwm,etim,rst : std_logic;
signal a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,emux_sin,emux_tri,epwm1,econt_35, pwm1_out,captura_int_0_aux: std_logic;
signal enr00,enr01,enr10,enr11,enr20,enr21,enr30,enr31,enr40,enr41: std_logic;
signal detr_0a,detr_0b,detr_0c,detr_1a,detr_1b,detr_1c,detr_2a,detr_2b,detr_2c,detr_3a,detr_3b,detr_3c,detr_4a,detr_4b,detr_4c:std_logic;
signal sdetr00,sdetr01,sdetr10,sdetr11,sdetr20,sdetr21,sdetr30,sdetr31,sdetr40,sdetr41:std_logic;
signal sel_rq0,sel_rq1,sel_rq2,sel_rq3,sel_rq4,sel_reg0,sel_regn0,sel_reg1,sel_regn1,sel_reg2,sel_regn2,sel_reg3,sel_regn3,sel_reg4,sel_regn4 : std_logic;
signal dton,dper,dcom0,dcom1,dcom2,dcom3,dcom4,dcap,cap0,cap1,cap2,cap3,cap4,dtimer,mux2_32a,mux2_32b,dton1,dper1: std_logic_vector (31 downto 0 );
signal capt0,capt1,capt2,capt3,capt4,qr_00,qr_01,qr_10,qr_11,qr_20,qr_21,qr_30,qr_31,qr_40,qr_41: std_logic_vector (31 downto 0 );
signal cont_35_out,mux2_6q : std_logic_vector(5 downto 0);




begin

-----------------------------------------------------
----------- INSTANTACION DE COMPONENTES -------------
-----------------------------------------------------


---- Detectores de flancos de los registros de captura

Inst_Detector_Flancos_r00 : Detector_Flancos port map(
			  clk 					=> clk,
           reset 					=> async_reset, 
           input 					=> sdetr00,
           out_falling_edge => open,
           out_rising_edge 	=> detr_0a
);

Inst_Detector_Flancos_r01 : Detector_Flancos port map(
			  clk 					=> clk,
           reset 					=> async_reset, 
           input 					=> sdetr01,
           out_falling_edge => open,
           out_rising_edge 	=> detr_0b
);

Inst_Detector_Flancos_r10 : Detector_Flancos port map(
			  clk 					=> clk,
           reset 					=> async_reset, 
           input 					=> sdetr10,
           out_falling_edge => open,
           out_rising_edge 	=> detr_1a
);

Inst_Detector_Flancos_r11 : Detector_Flancos port map(
			  clk 					=> clk,
           reset 					=> async_reset, 
           input 					=> sdetr11,
           out_falling_edge => open,
           out_rising_edge 	=> detr_1b
);

Inst_Detector_Flancos_r20 : Detector_Flancos port map(
			  clk 					=> clk,
           reset 					=> async_reset, 
           input 					=> sdetr20,
           out_falling_edge => open,
           out_rising_edge 	=> detr_2a
);

Inst_Detector_Flancos_r21 : Detector_Flancos port map(
			  clk 					=> clk,
           reset 					=> async_reset, 
           input 					=> sdetr21,
           out_falling_edge => open,
           out_rising_edge 	=> detr_2b
);

Inst_Detector_Flancos_r30 : Detector_Flancos port map(
			  clk 					=> clk,
           reset 					=> async_reset, 
           input 					=> sdetr30,
           out_falling_edge => open,
           out_rising_edge 	=> detr_3a
);

Inst_Detector_Flancos_r31 : Detector_Flancos port map(
			  clk 					=> clk,
           reset 					=> async_reset, 
           input 					=> sdetr31,
           out_falling_edge => open,
           out_rising_edge 	=> detr_3b
);

Inst_Detector_Flancos_r40 : Detector_Flancos port map(
			  clk 					=> clk,
           reset 					=> async_reset, 
           input 					=> sdetr40,
           out_falling_edge => open,
           out_rising_edge 	=> detr_4a
);

Inst_Detector_Flancos_r41 : Detector_Flancos port map(
			  clk 					=> clk,
           reset 					=> async_reset, 
           input 					=> sdetr41,
           out_falling_edge => open,
           out_rising_edge 	=> detr_4b
);



---- Detectores de el ultimo registro en el que se capturo el valor del contador

Inst_detr_0 : det_r port map(
			  a => detr_0a,
           b => detr_0b,
           c => detr_0c
);

Inst_detr_1 : det_r port map(
			  a => detr_1a,
           b => detr_1b,
           c => detr_1c
);

Inst_detr_2 : det_r port map(
			  a => detr_2a,
           b => detr_2b,
           c => detr_2c
);

Inst_detr_3 : det_r port map(
			  a => detr_3a,
           b => detr_3b,
           c => detr_3c
);

Inst_detr_4 : det_r port map(
			  a => detr_4a,
           b => detr_4b,
           c => detr_4c
);



---- Multiplexor que selecciona entre los dos registros de captura

Inst_Mux32_0 : Mux2_32 port map (
			  async_reset 	=> async_reset,
           a 				=> qr_00,
			  b 				=> qr_01,
			  q 				=> capt0,
			  sel 			=> sel_rq0	  
);


Inst_Mux32_1 : Mux2_32 port map (
			  async_reset 	=> async_reset,
           a 				=> qr_10,
			  b 				=> qr_11,
			  q 				=> capt1,
			  sel 			=> sel_rq1	  
);


Inst_Mux32_2 : Mux2_32 port map (
			  async_reset 	=> async_reset,
           a 				=> qr_20,
			  b 				=> qr_21,
			  q 				=> capt2,
			  sel 			=> sel_rq2	  
);


Inst_Mux32_3 : Mux2_32 port map (
			  async_reset 	=> async_reset,
           a 				=> qr_30,
			  b 				=> qr_31,
			  q 				=> capt3,
			  sel 			=> sel_rq3	  
);


Inst_Mux32_4 : Mux2_32 port map (
			  async_reset 	=> async_reset,
           a 				=> qr_40,
			  b 				=> qr_41,
			  q 				=> capt4,
			  sel 			=> sel_rq4	  
);



---- Puertas XOR para controlar la eleccion de registro de captura

Inst_xor2_0 : xor_2 port map(
			  a => sel2,
           b => detr_0c,
           c => sel_rq0
);

Inst_xor2_1 : xor_2 port map(
			  a => sel2,
           b => sel_reg1,
           c => sel_rq1
);

Inst_xor2_2 : xor_2 port map(
			  a => sel2,
           b => sel_reg2,
           c => sel_rq2
);

Inst_xor2_3 : xor_2 port map(
			  a => sel2,
           b => sel_reg3,
           c => sel_rq3
);

Inst_xor2_4 : xor_2 port map(
			  a => sel2,
           b => sel_reg4,
           c => sel_rq4
);



---- Inversores para la habilitacion de los registros de captura

Inst_inv_0 : inv port map (
			E 	=> sel_reg0,
			Q 	=> sel_regn0
);

Inst_inv_1 : inv port map (
			E 	=> sel_reg1,
			Q 	=> sel_regn1
);

Inst_inv_2 : inv port map (
			E 	=> sel_reg2,
			Q 	=> sel_regn2
);

Inst_inv_3 : inv port map (
			E 	=> sel_reg3,
			Q 	=> sel_regn3
);

Inst_inv_4 : inv port map (
			E 	=> sel_reg4,
			Q 	=> sel_regn4
);




---- Registros para almacenar los valores capturados

Inst_Reg_32_00: Registro_32 port map (
			CLK 		=> clk,
			CLR		=> RST,
			EN			=> enr00, --sel_reg0,
			EN_CAP 	=> sel1,
         D 			=> cap0,			
			SDETR 	=> sdetr00,
         Q 			=> qr_00
);

Inst_Reg_32_01: Registro_32 port map (
			CLK 		=> clk,
			CLR		=> RST,
			EN			=> enr01,--sel_regn0,
			EN_CAP 	=> sel1,
         D 			=> cap0,
			SDETR 	=> sdetr01,
         Q 			=> qr_01
);

Inst_Reg_32_10: Registro_32 port map (
			CLK 		=> clk,
			CLR		=> RST,
			EN			=> enr10,
			EN_CAP 	=> sel1,
         D 			=> cap1,		
			SDETR 	=> detr_1a,
         Q 			=> qr_10
);

Inst_Reg_32_11: Registro_32 port map (
			CLK 		=> clk,
			CLR		=> RST,
			EN			=> enr11,
			EN_CAP 	=> sel1,
         D 			=> cap1,		
			SDETR 	=> detr_1b,
         Q 			=> qr_11
);


Inst_Reg_32_20: Registro_32 port map (
			CLK 		=> clk,
			CLR		=> RST,
			EN			=> enr20,
			EN_CAP 	=> sel1,
         D 			=> cap2,		
			SDETR 	=> detr_2a,
         Q 			=> qr_20
);

Inst_Reg_32_21: Registro_32 port map (
			CLK 		=> clk,
			CLR		=> RST,
			EN			=> enr21,
			EN_CAP 	=> sel1,
         D 			=> cap2,		
			SDETR 	=> detr_2b,
         Q 			=> qr_21
);


Inst_Reg_32_30: Registro_32 port map (
			CLK 		=> clk,
			CLR		=> RST,
			EN			=> enr30,
			EN_CAP 	=> sel1,
         D 			=> cap3,		
			SDETR 	=> detr_3a,
         Q 			=> qr_30
);

Inst_Reg_32_31: Registro_32 port map (
			CLK 		=> clk,
			CLR		=> RST,
			EN			=> enr31,
			EN_CAP 	=> sel1,
         D 			=> cap3,		
			SDETR 	=> detr_3b,
         Q 			=> qr_31
);


Inst_Reg_32_40: Registro_32 port map (
			CLK 		=> clk,
			CLR		=> RST,
			EN			=> enr40,
			EN_CAP 	=> sel1,
         D 			=> cap4,		
			SDETR 	=> detr_4a,
         Q 			=> qr_40
);
Inst_Reg_32_41: Registro_32 port map (
			CLK 		=> clk,
			CLR		=> RST,
			EN			=> enr41,
			EN_CAP 	=> sel1,
         D 			=> cap4,		
			SDETR 	=> detr_4b,
         Q 			=> qr_41
);



---- Multiplexor que selecciona la direccion de la RAM 

Inst_Mux2_6 : Mux2_6 port map (
			  async_reset 	=> async_reset,
           a 				=> cont_35_out,
			  b 				=> direc_ram,
			  q 				=> mux2_6q,
			  sel 			=>	en11	  
);



---- Multiplexor que selecciona la entrada de datos de la RAM

Inst_Mux2_32 : Mux2_32 port map (
			  async_reset 	=> async_reset,
           a 				=> mux2_32a,
			  b 				=> mux2_32b,
			  q 				=> dton,
			  sel 			=> sel0	  
);



---- PWM para generar la frecuencia 36 veces mayor para la señal sinusoidal y triangular

Inst_pwm_1: pwm port map(
				async_reset => async_reset,
				sync_reset 	=> rst,
				en 			=> epwm1,
				clk 			=> clk_100,
				ton 			=> dton1,
				per 			=> dper1,
				q 				=> pwm1_out
);	



---- Contador para seleccionar la direccion de la RAM

Inst_Cont_35 : Cont_35 port map(
			  en 				=> econt_35,
           async_reset 	=> async_reset, 
           sync_reset 	=> rst,
           clk 			=> pwm1_out,
           q 				=> cont_35_out
);


--Inst_Mux_sin : Mux_sin port map (
--			  en 		=> emux_sin,
--			  sel 	=> cont_35_out,
--			  salida => mux3b
--);
--
--Inst_Mux_tri : Mux_tri port map (
--			  en 		=> emux_tri,
--			  sel 	=> cont_35_out,
--			  salida => mux3c	
--);



---- Memoria RAM con los valores para generar las señales

Inst_ram_valores : ram_valores port map(
			 CLK  =>	clk,
			 WE	=>	wr_ram,   
			 EN   => eram_valores,
          ADDR => mux2_6q,
          DI   => datos,
          DO   => mux2_32b
);


---- Puerta OR para la habilitacion de la RAM

Inst_or_2 : or_2 port map(
			  a => en11,
           b => eram_v,
           c => eram_valores
);




Inst_Valor_Periodo_1: Biestable_D port map(
				async_reset	=> async_reset,
				en 			=> en9_1,
				clk 			=> clk,
				d 				=> datos,
				sync_reset 	=> '0',
				q 				=> dper1
);


Inst_Valor_Ton_1 : Biestable_D port map(
				async_reset => async_reset,
				en 			=> en10_1,
				clk 			=> clk,
				d 				=> datos,
				sync_reset 	=> '0',
				q				=> dton1
);	


--------------------------------------------

Inst_retardador : Retardador port map(
			  async_reset => async_reset, 
           sync_reset => rst,
           clk => clk,
				q=>cpt0,
			  entrada=>captu0
);
-------------------------------------------


Inst_Mux_in: Mux_in port map(
			async_reset => async_reset,
         en 			=> en_mux,
         sel 				=> direc,
         sync_reset 	=>'0', 
         q(0)			=> en0,
			q(1) 			=> en1,
			q(2) 			=> en2,
			q(3) 			=> en3,
			q(4) 			=> en4,
			q(5)			=> en5,
			q(6) 			=> en6,
			q(7) 			=> en7,
			q(8) 			=> en8,
			q(9) 			=> en9,    --- Diferente
			q(10) 		=> en10,   --- Diferente
			q(11)			=> en11
);

		
Inst_Valor_Periodo: Biestable_D port map(
				async_reset	=> async_reset,
				en 			=> en2_1,
				clk 			=> clk,
				d 				=> datos,
				sync_reset 	=> '0',
				q 				=> dper
);

				
Inst_Valor_Ton : Biestable_D port map(
				async_reset => async_reset,
				en 			=> en3_1,
				clk 			=> clk,
				d 				=> datos,
				sync_reset 	=> '0',
				q 				=> mux2_32a
);				


Inst_Valor_comparacion_0 : Biestable_D port map(
				async_reset => async_reset,
				en 			=> en4_1,
				clk 			=> clk,
				d 				=> datos,
				sync_reset 	=> '0',
				q 				=> dcom0
);		
		
Inst_Valor_comparacion_1 : Biestable_D port map(
				async_reset => async_reset,
				en 			=> en5_1,
				clk 			=> clk,
				d 				=> datos,
				sync_reset 	=> '0',
				q 				=> dcom1
);		

Inst_Valor_comparacion_2 : Biestable_D port map(
				async_reset => async_reset,
				en 			=> en6_1,
				clk 			=> clk,
				d 				=> datos,
				sync_reset 	=> '0',
				q 				=> dcom2
);		

Inst_Valor_comparacion_3 : Biestable_D port map(
				async_reset => async_reset,
				en 			=> en7_1,
				clk 			=> clk,
				d 				=> datos,
				sync_reset 	=> '0',
				q 				=> dcom3
);	
				
Inst_Valor_comparacion_4 : Biestable_D port map(
				async_reset => async_reset,
				en 			=> en8_1,
				clk 			=> clk,
				d 				=> datos,
				sync_reset 	=> '0',
				q 				=> dcom4
);	

Inst_Valor_timer : Biestable_D port map(
				async_reset => async_reset,
				en => en1_1,
				clk => clk,
				d => datos,
				sync_reset => '0',
				q => dtimer
				);					
				
Inst_Detector_Flancos_0 : Detector_Flancos port map(
			  clk => clk,
           reset => async_reset, 
           input => captura_0,
           out_falling_edge => open,
           out_rising_edge => captur0
);

Inst_Detector_Flancos_1 : Detector_Flancos port map(
			  clk => clk,
           reset => async_reset, 
           input => captura_1,
           out_falling_edge => open,
           out_rising_edge => captur1
);

Inst_Detector_Flancos_2 : Detector_Flancos port map(
			  clk => clk,
           reset => async_reset, 
           input => captura_2,
           out_falling_edge => open,
           out_rising_edge => captur2
);

Inst_Detector_Flancos_3 : Detector_Flancos port map(
			  clk => clk,
           reset => async_reset, 
           input => captura_3,
           out_falling_edge => open,
           out_rising_edge => captur3
);

Inst_Detector_Flancos_4 : Detector_Flancos port map(
			  clk => clk,
           reset => async_reset, 
           input => captura_4,
           out_falling_edge => open,
           out_rising_edge => captur4
);
		
		
				
Inst_pwm: pwm port map(
				async_reset => async_reset,
				sync_reset 	=> rst,
				en 			=> epwm,
				clk 			=> clk_100,
				ton 			=> dton,
				per 			=> dper,
				q 				=> pwm_out
				);	

				
Inst_reg_captura_0 : reg_captura port map(
			  async_reset 	=> async_reset,
			  sync_reset	=> rst,
           en 				=> ecap,
			  lec 			=> sel1,
           clk 			=> clk,
           d 				=> dcap,
			  captura 		=> captur0,
			  sel_r			=> sel_reg0,
			  q 				=> cap0,
           int_salida 	=> captu0
			  );	
			
Inst_reg_captura_1 : reg_captura port map(
			  async_reset 	=> async_reset,
			  sync_reset 	=> rst,
           en 				=> ecap,
			  lec 			=> sel1,
           clk 			=> clk,
           d 				=> dcap,
			  captura 		=> captur1,
			  sel_r			=> sel_reg1,
			  q 				=> cap1,
           int_salida 	=> captu1
);

Inst_reg_captura_2 : reg_captura port map(
			  async_reset 	=> async_reset,
			  sync_reset 	=> rst,
           en 				=> ecap,
			  lec 			=> sel1,
           clk 			=> clk,
           d 				=> dcap,
			  captura 		=> captur2,
			  sel_r			=> sel_reg2,
			  q 				=> cap2,
           int_salida 	=> captu2
);

Inst_reg_captura_3 : reg_captura port map(
			  async_reset 	=> async_reset,
			  sync_reset 	=> rst,
           en 				=> ecap,
			  lec 			=> sel1,
           clk 			=> clk,
           d 				=> dcap,
			  captura 		=> captur3,
			  sel_r			=> sel_reg3,
			  q 				=> cap3,
           int_salida 	=> captu3
);
	
Inst_reg_captura_4 : reg_captura port map(
			  async_reset 	=> async_reset,
			  sync_reset 	=> rst,
           en 				=> ecap,
			  lec 			=> sel1,
           clk 			=> clk,
           d 				=> dcap,
			  captura 		=> captur4,
			  sel_r			=> sel_reg4,
			  q 				=> cap4,
           int_salida 	=> captu4
);


Inst_Unidad_Control : Unidad_Control port map(
			  d(0) 				=> uc0,
			  d(1) 				=> uc1,
			  pwm_conf			=> sel0,
--			  cap_stop			=> sel1,
			  clk 				=> clk,
			  async_reset 		=> async_reset,
--			  en_contador 		=> econ,
--			  en_mux 			=> emux,
			  en_timer 			=> etim,
			  en_captura 		=> ecap,
			  en_comparador	=> ecom,
			  en_pwm 			=> epwm,
--			  en_mux_sin		=> emux_sin,
--			  en_mux_tri		=> emux_tri,
			  en_cont_35		=> econt_35,
			  en_pwm_1			=> epwm1,
			  en_ram_v			=> eram_v,
--			  estado 			=> estado,
			  sync_reset 		=> rst
);
			  
			  
Inst_comparador_0 : Comparador port map(
			  async_reset => async_reset,
			  sync_reset => rst,
			  en => ecom,
           dato => dcom0,
			  timer => dcap,
			  compara_out => compara_out_0,
           compara_int => compa0
			  );		
			  
Inst_comparador_1 : Comparador port map(
			  async_reset => async_reset,
			  sync_reset => rst,
			  en => ecom,
           dato => dcom1,
			  timer => dcap,
			  compara_out => compara_out_1,
           compara_int => compa1
			  );		

Inst_comparador_2 : Comparador port map(
			  async_reset => async_reset,
			  sync_reset => rst,
			  en => ecom,
           dato => dcom2,
			  timer => dcap,
			  compara_out => compara_out_2,
           compara_int => compa2
			  );	
			 
Inst_comparador_3 : Comparador port map(
			  async_reset => async_reset,
			  sync_reset => rst,
			  en => ecom,
           dato => dcom3,
			  timer => dcap,
			  compara_out => compara_out_3,
           compara_int => compa3
			  );		
			  
Inst_comparador_4 : Comparador port map(
			  async_reset => async_reset,
			  sync_reset => rst,
			  en => ecom,
           dato => dcom4,
			  timer => dcap,
			  compara_out => compara_out_4,
           compara_int => compa4
			  );		

 


Inst_timer : timer port map(
				async_reset => async_reset,
				sync_reset => rst,
            en => etim,
            clk => clk_100,
			   q => dcap,
				load => a0,
            d =>dtimer
);

--Inst_Contador : Contador port map(
--			  en => econ,
--           async_reset => async_reset, 
--           sync_reset => rst,
--           clk => clk,
--           q(0)=> f2,
--			  q(1)=> f4,
--			  q(2)=> f8,
--			  q(3)=> f16
--);
--
--Inst_Mux_clk : Mux_clk port map (
--			  async_reset => async_reset,
--           en => emux,
--			  in0 => clk,
--			  in1 => f2,
--			  in2 => f4,
--			  in3=> f8,
--			  in4 =>  f16,
--           sel(0) =>sel0,
--			  sel(1) =>sel1,
--			  sel(2) =>sel2,
--           sync_reset => rst,
--           q => clk1
--);



Inst_R_Conf : R_Conf port map(
				async_reset =>async_reset,
           en => en0_1,
			  
           clk => clk,
           d => datos(15 downto 0),
           sync_reset => '0',
			  q(0) => uc0,
			  q(1) => uc1,
			  q(2) => sel0,
			  q(3) => sel1,
			  q(4) => sel2,
			  q(5) =>a0, 
			  q(6) =>a1, 
			  q(7) =>a2, 
			  q(8) =>a3, 
			  q(9) =>a4,
			  q(10) =>a5,
			  q(11) =>a6,
			  q(12) =>a7,
			  q(13) =>a8,
			  q(14) =>a9,
			  q(15) =>a10,
			  

           captura_0 => captura_int_0,             --Salida para avisar al uC de las interrupciones de captura
			  captura_1 => captura_int_1,             --Salida para avisar al uC de las interrupciones de captura
			  captura_2 => captura_int_2,             --Salida para avisar al uC de las interrupciones de captura
			  captura_3 => captura_int_3,             --Salida para avisar al uC de las interrupciones de captura
			  captura_4 => captura_int_4,             --Salida para avisar al uC de las interrupciones de captura
			  comparacion_0 => compara_int_0,	  --Salida para avisar al uC de las interrupciones de comparacion_0
			  comparacion_1 => compara_int_1,	  --Salida para avisar al uC de las interrupciones de comparacion_1
			  comparacion_2 => compara_int_2,     --Salida para avisar al uC de las interrupciones de comparacion_2
			  comparacion_3 => compara_int_3,     --Salida para avisar al uC de las interrupciones de comparacion_3
			  comparacion_4 => compara_int_4,     --Salida para avisar al uC de las interrupciones de comparacion_4
			  in_captura_0 => cpt0,--captu0, 
			  in_captura_1 => captu1, 
			  in_captura_2 => captu2, 
			  in_captura_3 => captu3, 
			  in_captura_4 => captu4, 
			  in_comparacion_0 => compa0,
			  in_comparacion_1 => compa1,
			  in_comparacion_2 => compa2,
			  in_comparacion_3 => compa3,
			  in_comparacion_4 => compa4
           );
			  
Inst_and_2_0 : and_2 port map(
			  a => wr,
           b => en0,
           c => en0_1
);
	
Inst_and_2_1 : and_2 port map(
				a => wr,
				b => en1,
				c => en1_1
			);
		
Inst_and_2_2 : and_2 port map(
				a => wr,
				b => en2,
				c => en2_1
);	

Inst_and_2_3 : and_2 port map(
				a => wr,
				b => en3,
				c => en3_1
);

Inst_and_2_4 : and_2 port map(
				a => wr,
				b => en4,
				c => en4_1
);

Inst_and_2_5 : and_2 port map(
				a => wr,
				b => en5,
				c => en5_1
);

Inst_and_2_6 : and_2 port map(
				a => wr,
				b => en6,
				c => en6_1
);

Inst_and_2_7 : and_2 port map(
				a => wr,
				b => en7,
				c => en7_1
);

Inst_and_2_8 : and_2 port map(
				a => wr,
				b => en8,
				c => en8_1
);

Inst_and_2_9 : and_2 port map(
				a => wr,
				b => en9,
				c => en9_1
);

Inst_and_2_10 : and_2 port map(
				a => wr,
				b => en10,
				c => en10_1
);

Inst_and_2_11 : and_2 port map(
				a => wr,
				b => en11,
				c => wr_ram
);

Inst_and_2_12 : and_2 port map(
				a => sel_regn0,
				b => captu0,
				c => enr01
);
Inst_and_2_13 : and_2 port map(
				a => sel_reg0,
				b => captu0,
				c => enr00
);

Inst_and_2_14 : and_2 port map(
				a => sel_regn1,
				b => captu1,
				c => enr11
);
Inst_and_2_15 : and_2 port map(
				a => sel_reg1,
				b => captu1,
				c => enr10
);
Inst_and_2_16 : and_2 port map(
				a => sel_regn2,
				b => captu2,
				c => enr21
);
Inst_and_2_17 : and_2 port map(
				a => sel_reg2,
				b => captu2,
				c => enr20
);
Inst_and_2_18 : and_2 port map(
				a => sel_regn3,
				b => captu3,
				c => enr31
);
Inst_and_2_19 : and_2 port map(
				a => sel_reg3,
				b => captu3,
				c => enr30
);
Inst_and_2_20 : and_2 port map(
				a => sel_regn4,
				b => captu4,
				c => enr41
);
Inst_and_2_21 : and_2 port map(
				a => sel_reg4,
				b => captu4,
				c => enr40
);


Inst_multiplex_salida : multiplex_salida port map(
				async_reset => async_reset,
				en => '1',
				in0(0) => uc0,
				in0(1) => uc1,
				in0(2) => sel0,
				in0(3) => sel1,
				in0(4) => sel2,
				in0(5) =>a0,
				in0(6) =>a1,
				in0(7) =>a2,
				in0(8) =>a3,
				in0(9) =>a4,
				in0(10) =>a5,
				in0(11) =>a6,
				in0(12) =>a7,
				in0(13) =>a8,
				in0(14) =>a9,
				in0(15) =>a10,
				in1 => dcap,
				in2 => dper,
				in3 => dton,
				in4 => dcom0,
				in5 => dcom1,
				in6 => dcom2,
				in7 => dcom3,
				in8 => dcom4,
				in9 => capt0,
				in10 => capt1,
				in11=> capt2,
				in12 =>capt3,
				in13 =>capt4,
				in14 =>mux2_32b,
				sel => sel_salida,
				sync_reset => rst,
				q => datos_out
				);




--valor_timer <= dcap;
--captura_dato0 <= capt0;
--captura_dato1 <= cap1;

end Behavioral;
