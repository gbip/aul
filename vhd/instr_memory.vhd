library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.common.all;


entity instr_memory is
	generic(
		LEN_SEL: natural := 16;
		LEN_INSTR: natural := 48
	);
	port(
		sel: in std_logic_vector(LEN_SEL-1 downto 0);
		q: out std_logic_vector(LEN_INSTR-1 downto 0)
	);
end entity;


architecture beh of instr_memory is

	signal instr_memory: instrArray := init_rom(filename => "prog.txt");

--	signal instr_memory: instrArray := (
--		0 => x"0000EF56DF75", -- MOV R0, 0x5
----		1 => NOP,
----		2 => NOP,
----		3 => NOP,e
--		1 => x"000100000002", -- MOV R1, 0x2
----		5 => NOP
----		6 => NOP,
----		7 => NOP,
--		2 => x"020000000001", -- ADD R0, R1 
----		9 => NOP,
----		10 => NOP,
----		11 => NOP,
--		3 => x"040000000001", -- MUL R0, R1 -> R0 = DEADBEEF
----		13 => NOP,
----		14 => NOP,
----		15 => NOP,
--		4 => x"070000000FA0", -- STORE R0, 0x4000
----		17 => NOP,
----		18 => NOP,
----		19 => NOP,
--		5 => x"060600000FA0", -- LOAD R6, 0x4000 --> R6 = 50
--		6 => x"000400000006",
--		7 => x"000200000006",
--		8 => x"000300000006",
--		9 => x"010500000006", -- COPY R5, R6 --> R5 = 50	 
--
--	--	12 => x"020100000000", -- ADD R1, R0
--	--	4 => x"040200000002", 
--	--	5 => x"07010001",
--	--	6 => x"00010102",
--		others => NOP
--	);

begin

	q <= instr_memory(to_integer(unsigned(sel(15 downto 0))));

end architecture;

