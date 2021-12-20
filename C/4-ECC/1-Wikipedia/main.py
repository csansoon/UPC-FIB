from colors import *
from message import get_message
from datos import *
from ecpy.curves import Point, Curve
import sympy

# MESSAGE
message = get_message()
print(f'{highlight}HASH DEL MENSAJE:{reset}\n{attribute}{message}{reset}\n')

# CURVE
curve = Curve.get_curve('secp256r1')
generator = curve.generator
print(f'{highlight}CURVA:{reset} {attribute}{curve.name}{reset}')
print(f'{highlight}GENERADOR:{reset} {attribute}{generator}{reset}')
print(f'{gray}y² = x² + {attribute}{curve.a}{gray}x + {attribute}{curve.b}{reset}\n')

# ORDER
order = curve.order
print(f'{highlight}ORDEN DE LA CURVA:{reset}\n{attribute}{order}{reset}')
if sympy.isprime(order):
    print(f'{good}✅ El orden es primo.{reset}\n')
else:
    print(f'{bad}❌ El orden no es primo.{reset}\n')

# PUBLIC KEY
public_key = Point(Qx, Qy, curve)
print(f'{highlight}CLAVE PÚBLICA:{reset}\n{attribute}({public_key.x}, {public_key.y}){reset}')
if curve.is_on_curve(public_key):
    print(f'{good}✅ La clave pública está en la curva.{reset}\n')
else:
    print(f'{bad}❌ La clave pública no está en la curva.{reset}\n')

# POINT ORDER
print(f'{highlight}ORDEN DEL PUNTO CLAVE PÚBLICA:{reset}')
print(f'{gray}El orden de la clave pública divide al orden de la curva. Como el orden de la curva es un primo, entonces el orden del punto es igual al de la curva.{reset}')
print(f'{attribute}{order}{reset}\n')

# VERIFICAR QUE LA FIRMA ES CORRECTA:
public_key = Point(Qx, Qy, curve, False)
w = pow(f2, -1, order)
u1 = message*w % order
u2 = f1*w % order
Punto_firma = u1*generator + u2*public_key
v = Punto_firma.x % order
if v == f1:
    print(f'{good}✅ Firma correcta.{reset}')
else:
    print(f'{bad}❌ Firma incorrecta.{reset}')
