----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:28:31 04/18/2019 
-- Design Name: 
-- Module Name:    fetch - Behavioral 
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

entity fetch is
    Port ( clk : in  STD_LOGIC;
           rst : in  STD_LOGIC;
           en : in  STD_LOGIC;
			  set_pc : in STD_LOGIC;
			  instr : out STD_LOGIC_VECTOR(47 downto 0);
			  pc_in : in STD_LOGIC_VECTOR(31 downto 0);
			  pc_out: out STD_LOGIC_VECTOR(31 downto 0)
			  );
end fetch;

architecture Behavioral of fetch is

	component instr_memory is
		generic(
		LEN_SEL: natural := 32;
		LEN_INSTR: natural := 48
	);
	port(
		sel: in std_logic_vector(LEN_SEL-1 downto 0);
		q: out std_logic_vector(LEN_INSTR-1 downto 0)
	);
	end component;
	signal pc : STD_LOGIC_VECTOR(31 downto 0);
begin

	memory : instr_memory port map(pc, instr);

process
begin
	wait until CLK'event and CLK='1';
	
		if RST='1' then 
			pc <= x"00000000";
		else if en ='1' then
			pc <= pc+1;
		end if;
		end if;
		
		
		if RST='0' and set_pc ='1' then
			pc <= pc_in;
		end if;
		
		
end process;

pc_out <= pc;

end Behavioral;

