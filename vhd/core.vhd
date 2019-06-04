----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:26:48 04/18/2019 
-- Design Name: 
-- Module Name:    core - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use work.common.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity core is
    Port ( clk : in  STD_LOGIC;
           en : in  STD_LOGIC;
           rst : in  STD_LOGIC;
			  x_w : out STD_LOGIC;
			  x_data : out STD_LOGIC_VECTOR(31 downto 0);
			  x_reg : out STD_LOGIC_VECTOR(7 downto 0);
			  print : out STD_LOGIC_VECTOR(7 downto 0)
			  );
end core;

architecture struct of core is
	component fetch
		Port ( clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           en : in  STD_LOGIC;
			  set_pc : in STD_LOGIC;
			  instr : out STD_LOGIC_VECTOR(47 downto 0);
			  pc_in : in STD_LOGIC_VECTOR(31 downto 0);
			  pc_out: out STD_LOGIC_VECTOR(31 downto 0));
	end component;
	component decoder
	    Port ( instr : in  STD_LOGIC_VECTOR (47 downto 0);
           opcode : out  STD_LOGIC_VECTOR (7 downto 0);
           reg : out  STD_LOGIC_VECTOR (7 downto 0);
           val : out  STD_LOGIC_VECTOR (31 downto 0));
	end component;
	component ual
		Port ( A : in  STD_LOGIC_VECTOR (31 downto 0);
           B : in  STD_LOGIC_VECTOR (31 downto 0);
			  DATA : in STD_LOGIC_VECTOR (31 downto 0);
			  PC : in STD_LOGIC_VECTOR (31 downto 0);
           Op : in  STD_LOGIC_VECTOR (7 downto 0);
           S : out  STD_LOGIC_VECTOR (31 downto 0);
           Flags : out  STD_LOGIC_VECTOR (3 downto 0)); -- CNZV
	end component;  
	component pipeline_early
		 Port ( en : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           input : in p_early;
			  output : out p_early);
	end component;
	component pipeline_late
		Port ( 	  
			  en : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           input : in p_late;
			  output : out p_late
			  );
	end component;
	component registers_bank
		    Port ( clk : in  STD_LOGIC;
           en : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           w : in  STD_LOGIC;
           reg1 : in  STD_LOGIC_VECTOR (7 downto 0);
           reg2 : in  STD_LOGIC_VECTOR (7 downto 0);
           reg1_out : out  STD_LOGIC_VECTOR (31 downto 0);
           reg2_out : out STD_LOGIC_VECTOR (31 downto 0);
           regw : in STD_LOGIC_VECTOR (7 downto 0);
			  data_in : in STD_LOGIC_VECTOR (31 downto 0)
			  );
	end component;
	component memory
		Port(
			clk : in  STD_LOGIC;
			en : in  STD_LOGIC;
			rst : in  STD_LOGIC;
			opcode : in  STD_LOGIC_VECTOR (7 downto 0);
			addr : in  STD_LOGIC_VECTOR (31 downto 0);
			data_in : in  STD_LOGIC_VECTOR (31 downto 0);
			data_out : out STD_LOGIC_VECTOR (31 downto 0)
		);
	end component;
	component pipe_last
	Port ( 	  
			 			  -- CONTROL SIGNALS
			  en : in  STD_LOGIC;
           clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           input : in p_last;
			  output : out p_last
			  );
	end component;
	component register_controler
	 Port ( rst : in  STD_LOGIC;
			  input : in p_last;
			  w : out STD_LOGIC;
			  data : out STD_LOGIC_VECTOR(31 downto 0);
			  reg : out STD_LOGIC_VECTOR(7 downto 0);
			  pc_w : out STD_LOGIC
			  );
	end component;
	component amu is
	Port(
		en : in  STD_LOGIC;
		clk : in  STD_LOGIC;
		rst : in  STD_LOGIC;
		input : in amu_interface;
		alea : out STD_LOGIC
	);
	end component;
	component print_unit is
	Port( clk : IN  std_logic;
         en : IN  std_logic;
         rst : IN  std_logic;
			data : in p_early;
			output : out STD_LOGIC_VECTOR (7 downto 0)
			);
	end component;

	
	signal s1_out, s1_out_norm, s1_out_NOP, s2_in : p_early;
	signal s2_out, s3_in : p_late;
	signal s3_out, s4_in : p_last;
	signal amu_i : amu_interface;
	signal w, alea, enableFetch, w_pc : STD_LOGIC;
	signal regw, opcodeNOP : STD_LOGIC_VECTOR (7 downto 0);
	signal data_in, pc : STD_LOGIC_VECTOR (31 downto 0);
	signal instr : STD_LOGIC_VECTOR (47 downto 0);
	
begin


	alea_unit : amu port map(clk, rst, en, amu_i, alea);
	print_u : print_unit port map(clk, en, rst, s2_in,print);
	-- First Stage
	enableFetch <= '1' when ( (en='1') and (alea='0')) else '0';
	fetch_m : fetch port map (clk, rst, enableFetch, w_pc, instr, data_in, pc);
	decode_m : decoder port map (instr, s1_out_norm.opcode, s1_out_norm.reg, s1_out_norm.val);
	registers_bank_m : registers_bank port map(clk, en, rst, w, s1_out.reg, s1_out.val(7 downto 0), s1_out_norm.d1, s1_out_norm.d2, regw, data_in);
	-- End First Stage
	
	pipe_1 : pipeline_early port map (en, clk, rst, s1_out, s2_in);
	
	-- 2nd stage
	alu : ual port map(s2_in.d1, s2_in.d2, s2_in.val, s2_in.pc, s2_in.opcode, s2_out.ual_output, s2_out.flags);
	s2_out.opcode <= s2_in.opcode;
	s2_out.reg <= s2_in.reg;
	s2_out.val <= s2_in.val;
	s2_out.d1 <= s2_in.d1;
	s2_out.d2 <= s2_in.d2;
	-- End 2nd stage
	
	pipe_2 : pipeline_late port map(en, clk, rst, s2_out, s3_in);
	
	-- 3rd stage
	mem : memory port map(clk, en, rst, s3_in.opcode, s3_in.val, s3_in.d1, s3_out.mem_readValue);
	s3_out.opcode <= s3_in.opcode;
	s3_out.firstOperand <= s3_in.reg;
	s3_out.ual_readValue <= s3_in.ual_output;
	s3_out.dataOperand <= s3_in.val;
	s3_out.secondRegData <= s3_in.d2;
	s3_out.firstRegData <= s3_in.d1;
	-- End 3rd stage
	
	pipe_3 : pipe_last port map(en, clk, rst, s3_out,s4_in);
	reg_controler : register_controler port map(rst, s4_in, w, data_in, regw, w_pc);
	x_w <= w;
	x_reg <= regw;
	x_data <= data_in;
	
	amu_i.instr_1.opcode <= s1_out_norm.opcode;
	amu_i.instr_1.reg <= s1_out_norm.reg;
	amu_i.instr_1.val <= s1_out_norm.val;
	
	amu_i.instr_2.opcode <= s2_in.opcode;
	amu_i.instr_2.reg <= s2_in.reg;
	amu_i.instr_2.val <= s2_in.val;
	
	amu_i.instr_3.opcode <= s3_in.opcode;
	amu_i.instr_3.reg <= s3_in.reg;
	amu_i.instr_3.val <= s3_in.val;
	
	amu_i.instr_4.opcode <= s4_in.opcode;
	amu_i.instr_4.reg <= s4_in.firstOperand;
	amu_i.instr_4.val <= s4_in.dataOperand;

	s1_out_NOP.opcode <= x"17";
	s1_out_NOP.reg <= x"00";
	s1_out_NOP.val <= x"00000000";
	s1_out_NOP.d1 <= x"00000000";
	s1_out_NOP.d2 <= x"00000000";
	s1_out_NOP.pc <= pc;
	
	s1_out_norm.pc <= pc;
	
	s1_out <= s1_out_NOP when (alea='1') else s1_out_norm;
	
end struct;

