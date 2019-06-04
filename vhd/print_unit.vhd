----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:26:29 05/27/2019 
-- Design Name: 
-- Module Name:    print_unit - Behavioral 
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
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.common.all;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity print_unit is
Port( clk : IN  std_logic;
         en : IN  std_logic;
         rst : IN  std_logic;
			data : in p_early;
			output : out STD_LOGIC_VECTOR (7 downto 0)
			);
end print_unit;

architecture Behavioral of print_unit is
	signal mem : STD_LOGIC_VECTOR (7 downto 0);
begin

process
begin
	wait until CLK'event and CLK='1';
	
		if RST='1' then 
			mem <= x"00";
		else if en ='1' and data.opcode = x"0D" then
			mem <= data.d1(7 downto 0);
		end if;
		end if;

end process;

output <= mem;


end Behavioral;

