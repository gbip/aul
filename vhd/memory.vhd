----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    17:20:51 05/07/2019 
-- Design Name: 
-- Module Name:    memory - Behavioral 
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

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity memory is
	Port(
		clk : in  STD_LOGIC;
      en : in  STD_LOGIC;
      rst : in  STD_LOGIC;
		opcode : in  STD_LOGIC_VECTOR (7 downto 0);
		addr : in  STD_LOGIC_VECTOR (31 downto 0);
		data_in : in  STD_LOGIC_VECTOR (31 downto 0);
		data_out : out STD_LOGIC_VECTOR (31 downto 0)
	);
end memory;

architecture Behavioral of memory is
	component memory_controller
	Port (  clk : in  STD_LOGIC;
           en : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           w : in  STD_LOGIC;
           data : in  STD_LOGIC_VECTOR (31 downto 0);
           addr : in  STD_LOGIC_VECTOR (31 downto 0);
			  data_out : out STD_LOGIC_VECTOR (31 downto 0));
	end component;
	
	signal addr_tmp : STD_LOGIC_VECTOR(31 downto 0) := x"00000FA0";
	signal w, mem_en : STD_LOGIC;
begin
	mem : memory_controller port map(clk, mem_en, rst, w, data_in, addr_tmp, data_out);

	mem_en <= '1' when (opcode = x"07" or opcode = X"06") and en='1' and rst = '0' else '0';
	w <= '1' when opcode = X"07" else '0';
	addr_tmp <= addr when en='1' else x"00000FA0";

end Behavioral;

