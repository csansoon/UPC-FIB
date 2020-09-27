import java.sql.*; 

class CtrlDadesPublic extends CtrlDadesPrivat {
	
	public ConjuntTuples consulta(Connection c, Tuple params) throws BDException {
		ConjuntTuples ct = new ConjuntTuples();
		
		String dniInput = params.consulta(1);
		for (int i = 2; !dniInput.equals("-999"); i++) {
			Tuple fila = new Tuple();
			
			fila.afegir(dniInput);	//dni del professor

	
	
		try {
			Statement s = c.createStatement();
			ResultSet r = s.executeQuery("select count(*) from assignacions where dni ='" + dniInput + "';");
			
			if (r.next()) {
				
				fila.afegir(r.getString(1));	//quantitat d'assignacions
			}
			s.close();
		}
		catch (SQLException se){
			throw new BDException(11);
		}

			ct.afegir(fila);
			
			dniInput = params.consulta(i);
		}
		
		
		return ct;
	}
}