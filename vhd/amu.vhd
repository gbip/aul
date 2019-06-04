----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:06:27 05/14/2019 
-- Design Name: 
-- Module Name:    amu - Behavioral 
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
use IEEE.NUMERIC_STD.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;


use work.common.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity amu is
Port(
	en : in  STD_LOGIC;
   clk : in  STD_LOGIC;
   rst : in  STD_LOGIC;
	input : in amu_interface;
	alea : out STD_LOGIC
	);

end amu;


architecture Behavioral of amu is

signal r1, w2, w3, w4 : STD_LOGIC;

	begin
	
	r1 <= '1' when not (input.instr_1.opcode = x"00" or input.instr_1.opcode = x"06" or input.instr_1.opcode = x"17") else '0';
	w2 <= '1' when not (input.instr_2.opcode = x"07" or input.instr_2.opcode = x"17") else '0';
	w3 <= '1' when not (input.instr_3.opcode = x"07" or input.instr_3.opcode = x"17") else '0';
	w4 <= '1' when not (input.instr_4.opcode = x"07" or input.instr_4.opcode = x"17") else '0';

--	alea <= r1;
							
		alea <= '1' when  ( (r1='1') and
							  (		((w2='1') and
											((input.instr_1.reg = input.instr_2.reg) or (input.instr_1.val(7 downto 0) = input.instr_2.reg) or (input.instr_2.opcode >= x"0D" and input.instr_2.opcode <= x"13")))
									or
										((w3='1') and
											((input.instr_1.reg = input.instr_3.reg) or (input.instr_1.val(7 downto 0) = input.instr_3.reg) or (input.instr_3.opcode >= x"0D" and input.instr_3.opcode <= x"13")))
									or ((w4='1') and
											((input.instr_1.reg = input.instr_4.reg) or (input.instr_1.val(7 downto 0) = input.instr_4.reg) or (input.instr_4.opcode >= x"0D" and input.instr_4.opcode <= x"13")))
								)
							)
						  else '0';


end Behavioral;

