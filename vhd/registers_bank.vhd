----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:50:13 04/18/2019 
-- Design Name: 
-- Module Name:    registers_bank - Behavioral 
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity registers_bank is
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
end registers_bank;

architecture Behavioral of registers_bank is
	type REGISTERS is array (0 to 7) of STD_LOGIC_VECTOR (31 downto 0);
	signal regs : REGISTERS := (others => (others => '0'));
begin

process
begin
	wait until CLK'event and CLK='1';
		if RST='1' then 
			regs <= (others => (others => '0'));
		else if en='1' then
			if w='1' then
				regs(to_integer(unsigned(regw(2 downto 0)))) <= data_in;
			end if;
			end if;
		end if;
end process;

reg1_out <= regs(to_integer(unsigned(reg1(2 downto 0)))) when en='1' and (reg1 <= 7)
	else X"00000000";
	
reg2_out <= regs(to_integer(unsigned(reg2(2 downto 0)))) when en='1' and (reg2 <= 7)
	else X"00000000";

end Behavioral;

