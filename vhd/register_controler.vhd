----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    13:48:59 05/10/2019 
-- Design Name: 
-- Module Name:    register_controler - Behavioral 
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

entity register_controler is
Port (           rst : in  STD_LOGIC;
			  input : in p_last;
			  w : out STD_LOGIC;
			  data : out STD_LOGIC_VECTOR(31 downto 0);
			  reg : out STD_LOGIC_VECTOR(7 downto 0);
			  pc_w : out STD_LOGIC
			  );
end register_controler;

architecture Behavioral of register_controler is

begin
	w <= '0' when (input.opcode = x"07" or input.opcode = x"0D" or (input.opcode >= X"0E" and input.opcode <= X"13") or input.opcode =x"17") or rst = '1'
	else '1';
	data <= (others => '0') when rst = '1' else
			  input.secondRegData when input.opcode = x"01" else
			  input.dataOperand when input.opcode = x"00" else
			  input.mem_readValue when input.opcode = x"06" else
			  input.ual_readValue;
	
	pc_w <= '1' when  (input.opcode >= x"0E" and input.opcode <= x"10") 
						or 
							(input.opcode >= x"11" and input.opcode <= x"13" and input.firstRegData = x"00000000")
	 else
				'0';
	
	reg <= (others => '0') when rst = '1' else input.firstOperand;
end Behavioral;

